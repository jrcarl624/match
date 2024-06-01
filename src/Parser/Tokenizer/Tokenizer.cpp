#include "Tokenizer.hpp"
#include <cstdint>
#include "../../Types/SlideView.hpp"
#include "../../Logs/Logs.hpp"
#include <chrono>
#define TOK_COMMENTS

namespace match::parser {
	Lexer::Lexer() {
	}

	Lexer::~Lexer() {
	}

	std::vector<Token> Lexer::Lex(SlideView<u8> source) {
		std::vector<Token> tokens = {};
		this->m_subTokens = source;
		this->m_window = this->m_subTokens.SubView();
		this->lastRowIndex = 0;

		while (this->m_subTokens.IsSubViewInBounds(m_window)) {
			//auto start = std::chrono::high_resolution_clock::now();
			Token token = this->NextToken();
 /*           auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
			LoggerInstance.Log("{}", LogLevel::LOG_DEBUG, std::format("Token Of Type {} Found! Token Value: '{}', took: {}", token.ToString(), token.GetSubTokensAsStr(), duration));
  */          tokens.push_back(token);
		};
		return tokens;
	}

	Token Lexer::NextToken() {
	//	this->next = 0;
		this->quote = 0;
		u8 magic_token;
	next_sub_token:
		this->current = this->m_window.Back();
		switch (static_cast<Token_e>(this->current)) {
			case Token_e::Newline: // Whitespace -----------------------
				this->IncrementRow();

			case horizontal_whitespace_tokens:
				this->m_window.SkipTail();
				goto next_sub_token;

			case Token_e::Divide: // Divide Operator -----------------------
#ifdef TOK_COMMENTS
				switch (this->SetCurrentPushBack<u8>()) { // Comments -----------------------

					case static_cast<u8>(Comment_E::MultiLineStart):
						this->SetTokenType(Token_e::Comment);
						while (this->m_window.PushBack<Token_e>() != Token_e::Newline);
						goto increment_and_return;

					case static_cast<u8>(Comment_E::MultiLineEnd): {
						this->SetTokenType(Token_e::Comment);
						commentLevel = 1;
						do { // test an offset of 1
							switch (this->m_window.PushBack<Comment_E>(1)) {
								case Comment_E::MultiLineStart:
									commentLevel++;
									break;
								case Comment_E::MultiLineEnd:
									commentLevel--;
									break;
							}
						} while (commentLevel);
						this->m_window.IncTail();
						goto increment_and_return;
					}
				};
#endif
			case operator_1_no_divide_tokens: { // Operators -----------------------
					magic_token = this->current + this->m_window.Back<u8>(1) + MAGIC_NUMBER;
					switch (static_cast<Token_e>(magic_token)) {
						case operator_2_tokens: {
								this->SetTokenType(magic_token);

								

								this->m_window.IncTail(1);
								goto increment_and_return;
							}
					}



					this->SetTokenType(this->current);
					goto increment_and_return;
				}

			case delimiter_tokens: { // Delimiters -----------------------
					this->SetTokenType(this->current);
					if (this->m_window.IsPopulated())
						this->m_window.IncTail();
					goto increment_and_return;
				}

			case quote_tokens: // Quotes -----------------------
				this->SetTokenType(this->current);
				quote = this->current;
				this->current = this->m_window.PushBack<u8>();
			parse_quote: // Parse the contents within the quotes
				switch (this->current) {
					case '\n': // Newline
						this->IncrementRow(); // Temp fix for newlines in strings
						this->lastRowIndex -= 2; // as this fixes the column calculation
						break;
					case '\\':  // Backslash
						if (this->m_window.Back(1) == quote)
							this->m_window.IncTail();
						break;
					default: // Closing quote
						if (this->current == quote)
							goto increment_and_return;
				};
				this->current = this->m_window.PushBack<u8>();
				if (this->m_subTokens.IsSubViewInBounds(m_window))
					goto parse_quote;
				this->incomplete = true; // TODO: Throw compiler error if incomplete
				goto return_token;

			case numeric_tokens: // Numeric Literals -----------------------
				this->SetTokenType(Token_e::IntegerLiteral);
			number: // Parse the rest of the number
				switch (this->SetCurrentPushBack<Token_e>()) {
					case Token_e::DotAccess: // Check for decimal point and set type to float if not already a float
						if (this->currentType == Token_e::FloatLiteral) {
							this->SetTokenType(Token_e::Invalid); // If there is another dot then it is invalid
							goto increment_and_return;
						}
						this->SetTokenType(Token_e::FloatLiteral);
					case numeric_tokens:
					case Token_e::Underscore: // A numeric separator
						if (this->m_subTokens.IsSubViewInBounds(m_window))
							goto number;
					default:
						goto return_token;
				};

			case uppercase_tokens: // Identifiers -----------------------
			case lowercase_tokens:
			case Token_e::Underscore:
				this->SetTokenType(Token_e::Identifier);
			identifier: // Parse the rest of the identifier
				switch (this->m_window.Back<Token_e>(1)) {
					case uppercase_tokens:
					case lowercase_tokens:
					case numeric_tokens:
					case Token_e::Underscore:
						if (this->m_subTokens.IsSubViewInBounds(m_window))
							this->m_window.IncTail();
						goto identifier;
					default:
						goto increment_and_return;
				}

			default: // Invalid Tokens -----------------------
				this->SetTokenType(Token_e::Invalid);
				goto increment_and_return;
		}

		this->m_window.IncTail(); // Increment the tail

		if (this->m_subTokens.IsSubViewInBounds(m_window)) // Check if the window is in bounds
			goto next_sub_token;

	increment_and_return_set_current:
		this->SetTokenType(current);

	increment_and_return:
		this->m_window.IncTail();

	return_token:
		Token token(this->m_window, reinterpret_cast<u64>(this->m_window.GetHead() - this->lastRowIndex), this->row, this->currentType);
		this->m_window.SetHeadToTail();
		this->SetTokenType(Token_e::Invalid);
		return token;
	}
}
