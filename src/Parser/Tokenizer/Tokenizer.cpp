#include "Tokenizer.hpp"
#include <cstdint>
#include "../../Types/SlideView.hpp"
namespace Match::Parser
{
	Tokenizer::Tokenizer()
	{
	}
	Tokenizer::~Tokenizer()
	{
	}

	std::vector<Token> Tokenizer::Tokenize(SlideView<u8> source)
	{
		std::vector<Token> tokens = {};
		this->m_subTokens = source;
		this->m_window = this->m_subTokens.Window();
		this->lastRowIndex = 0;

		while (this->m_subTokens.IsWindowExhausted(m_window))
			tokens.push_back(this->NextToken());
		return tokens;
	}

	Token Tokenizer::NextToken()
	{
		u8 peek = this->m_window.Back<u8>();
		u8 quote;
		u8 commentNestLevel;

	next_sub_token:

		switch (static_cast<Whitespace_E>(peek))
		{
		case Whitespace_E::Newline:
			this->IncrementRow();
		case Whitespace_E::CarriageReturn:
		case Whitespace_E::FormFeed:
		case Whitespace_E::Space:
		case Whitespace_E::Tab:
		{
			this->m_window.Skip();
			goto next_iteration;
		};
		}

		// 2 char operators -----------------------
		switch (this->m_window.Back<OperatorTwo_E>())
		{
		case OperatorTwo_E::Or:
		case OperatorTwo_E::And:
		case OperatorTwo_E::ShiftLeft:
		case OperatorTwo_E::ShiftRight:
		case OperatorTwo_E::AddAssign:
		case OperatorTwo_E::SubtractAssign:
		case OperatorTwo_E::MultiplyAssign:
		case OperatorTwo_E::DivideAssign:
		case OperatorTwo_E::ModuloAssign:
		case OperatorTwo_E::Equal:
		case OperatorTwo_E::BitwiseXorAssign:
		case OperatorTwo_E::NotEqual:
		case OperatorTwo_E::BitwiseAndAssign:
		case OperatorTwo_E::BitwiseOrAssign:
		case OperatorTwo_E::Return:
		case OperatorTwo_E::LessThanOrEqual:
		case OperatorTwo_E::GreaterThanOrEqual:
		case OperatorTwo_E::ScopeResolution:
		{
			this->SetTokenType(Token_E::Operator);
			this->m_window.IncTail(1);
			goto next_iteration;
		}
		}

		// 1 char operators -----------------------
		switch (static_cast<OperatorOne_E>(peek))
		{
		case OperatorOne_E::Not:
		case OperatorOne_E::BitwiseOr:
		case OperatorOne_E::BitwiseAnd:
		case OperatorOne_E::BitwiseXor:
		case OperatorOne_E::Add:
		case OperatorOne_E::Subtract:
		case OperatorOne_E::Multiply:
		case OperatorOne_E::Divide:
		case OperatorOne_E::Modulo:
		case OperatorOne_E::Equal:
		case OperatorOne_E::LessThan:
		case OperatorOne_E::GreaterThan:
		case OperatorOne_E::Access:
		case OperatorOne_E::Optional:
		{
			this->SetTokenType(Token_E::Operator);
			goto next_iteration;
		}
		}

		// Delimiters -----------------------
		switch (static_cast<Delimiter_E>(peek))
		{
		case Delimiter_E::OpenBrace:
		case Delimiter_E::CloseBrace:
		case Delimiter_E::OpenParenthesis:
		case Delimiter_E::CloseParenthesis:
		case Delimiter_E::OpenSquareBracket:
		case Delimiter_E::CloseSquareBracket:
		case Delimiter_E::ListSeparator:
		case Delimiter_E::TypeSeparator:
		{
			this->SetTokenType(Token_E::Delimiter);

			// breaks nested switch in loop
			if (this->m_window.IsPopulated())
				this->m_window.IncTail();
			goto next_iteration;
		};
		}

		// Quotes -----------------------
		quote = peek;
		switch (static_cast<Quote_E>(peek))
		{
		case Quote_E::Single:
			this->SetTokenType(Token_E::CharLiteral);
			goto parse_quote;
		case Quote_E::Double:
			this->SetTokenType(Token_E::StringLiteral);
		parse_quote:

			this->m_window.IncTail();

			switch (peek = this->m_window.Back<u8>())
			{
			// Newline
			case '\n':
			{
				this->IncrementRow();
				// Temp fix for newlines in strings
				// as this fixes the column calculation
				this->lastRowIndex -= 2;
				break;
			}

			// Backslash
			case '\\':
			{
				if (this->m_window.Back(1) == quote)
					this->m_window.IncTail();
				goto next_iteration;
			}

			// Closing quote
			default:
				if (peek == quote)
					goto next_iteration;
			};

			if (this->m_window.IsPopulated())
				goto parse_quote;

			// TODO: Throw compiler error if incomplete
			goto return_token;
		}

		// check for negative numbers

		// Numbers -----------------------
		if (std::isdigit(peek) && this->m_window.IsEmpty())
		{
		number_set:

			this->SetTokenType(Token_E::Number);
		number:
			while (std::isdigit(this->m_window.Push<u8>()))

				if (this->m_window.Back<u8>() == '.')
					goto number;

			goto next_iteration;
		}

		// Comments -----------------------

		if (this->m_window.Back() == '/')
		{
			peek = this->m_window.Push();

			switch (peek)
			{
			case static_cast<u8>(Comment_E::MultiLineStart):

				while (this->m_window.Push() != '\n')

					;
				break;
			case static_cast<u8>(Comment_E::MultiLineEnd):
			{
				commentNestLevel = 1;
				while (commentNestLevel)
				{
					// test an offset of 1
					switch (this->m_window.Push<Comment_E>())
					{
					case Comment_E::MultiLineStart:
						commentNestLevel++;
						break;
					case Comment_E::MultiLineEnd:
						commentNestLevel--;
						break;
					}
				}
			}
			}

			goto next_iteration;
		}

		// Keywords -----------------------

		// Chars
		switch (this->m_window.Back<u8>(1))
		{
		case static_cast<u8>(OperatorTwo_E::And):
		case static_cast<u8>(OperatorTwo_E::ShiftLeft):
		case static_cast<u8>(OperatorTwo_E::ShiftRight):
		case static_cast<u8>(OperatorTwo_E::AddAssign):
		case static_cast<u8>(OperatorTwo_E::SubtractAssign):
		case static_cast<u8>(OperatorTwo_E::MultiplyAssign):
		case static_cast<u8>(OperatorTwo_E::DivideAssign):
		case static_cast<u8>(OperatorTwo_E::ModuloAssign):
		case static_cast<u8>(OperatorTwo_E::BitwiseXorAssign):
		case static_cast<u8>(OperatorTwo_E::Equal):
		case static_cast<u8>(OperatorTwo_E::NotEqual):
		case static_cast<u8>(OperatorOne_E::Access):
		case static_cast<u8>(OperatorOne_E::Optional):
		case static_cast<u8>(Delimiter_E::ListSeparator):
		case static_cast<u8>(Delimiter_E::TypeSeparator):

		{
			this->SetTokenType(Token_E::Identifier);
			goto next_iteration;
		}
		}

	next_iteration:
		peek = this->m_window.Push();

		if (this->m_window.IsPopulated())
			goto next_sub_token;

	return_token:
		Token token( this->m_window, reinterpret_cast<u64>(this->m_window.GetHead() - this->lastRowIndex), this->row, this->currentType);
		this->m_window.reset();
		return token;
	}
}