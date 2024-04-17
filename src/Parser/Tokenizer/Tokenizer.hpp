#pragma once
#include <string>
#include "TokenTypes.hpp"
#include "../../types.hpp"
#include "../../Types/SlideView.hpp"
#include "../../Types/RangeGeneration.hpp"
#include "Token.hpp"
#include <vector>


#define getFirstByte(shor) (static_cast<u8>(shor >> 8))

namespace Match::Parser
{

	class Tokenizer
	{
		/*
		  pub fn new(chars: &'cxx [u8], starting_row: isize) -> Self {
		Tokenizer {
			sub_tokens: chars,
			sub_tokens_start: chars.as_ptr(),
			sub_tokens_end: unsafe { chars.as_ptr().add(chars.len()) },
			head: chars.as_ptr(),
			tail: chars.as_ptr(),
			row: starting_row,
			incomplete: false,
			last_row_index: 0,
		}
	}

	/// Allows the tokenizer to be reset with new content without reallocation,
	pub fn reset(&mut self, content: &'cxx [u8], starting_row: isize) {
		self.sub_tokens = content;
		self.sub_tokens_start = self.sub_tokens.as_ptr();
		self.sub_tokens_end = unsafe { self.sub_tokens.as_ptr().add(content.len()) };
		self.tail = content.as_ptr();
		self.head = content.as_ptr();
		self.row = starting_row;
		self.incomplete = false;
		self.last_row_index = 0;
	}*/
	public:
		Tokenizer();

		
		~Tokenizer();

		std::vector<Token> Tokenize(SlideViewChar source);
	

		inline Token NextToken();

		inline void IncrementRow()
		{
			this->lastRowIndex = this->m_subTokens.IndexOf(this->m_window.GetHead()) - this->m_window.Size();
			this->row++;
		}

		inline void SetTokenType(TokenType type)
		{
			this->currentType = type;
		}
		inline Token CreateToken()
		{

			Token token(this->m_window, reinterpret_cast<uSize>(this->m_window.GetHead() - this->lastRowIndex), this->row, this->currentType);
			this->m_window.reset();
			return token;
		}

	private:
	private:
		SlideViewChar m_subTokens = {};
		SlideViewChar m_window = {};
		uSize row = 0;
		uSize lastRowIndex = 0;
		TokenType currentType = TokenType::Unknown;
	};

	enum class Delimiters : u8
	{
		OpenBrace = '{',
		CloseBrace = '}',
		OpenParenthesis = '(',
		CloseParenthesis = ')',
		OpenSquareBracket = '[',
		CloseSquareBracket = ']',
	};

	constexpr u8 listSeparator = ',';
	constexpr u8 scopeResolution = ';';
	constexpr u8 typeSeparator = ':';
	constexpr u8 newLine = '\n';

	enum class OtherWhitespace : u8
	{
		Tab = '\t',
		FormFeed = '\x0C',
		CarriageReturn = '\r',
		Space = ' '
	};

	enum class Whitespace : u8
	{
		Tab = OtherWhitespace::Tab,
		FormFeed = OtherWhitespace::FormFeed,
		CarriageReturn = OtherWhitespace::CarriageReturn,
		Space = OtherWhitespace::Space,
		Newline = '\n'

	};

	constexpr u8 stringQuotes = '"';
	constexpr u8 charQuotes = '\'';
	constexpr u8 backslash = '\\';

	enum class QuotePrefixes : u8
	{
		Raw = 'r',
		Binary = 'b',
		Unicode = 'u',
		Formatted = 'f'
	};

	enum class Quotes :u8 {
		Single ='\'',
		Double = '"'
	};

	enum class Operator1 : u8
	{
		BitwiseOr = '|',
		BitwiseAnd = '&',
		BitwiseXor = '^',
		Not = '!',
		Add = '+',
		Subtract = '-',
		Multiply = '*',
		Divide = '/',
		Modulo = '%',
		Equal = '=',
		NotEqual = '!',
		LessThan = '<',
		GreaterThan = '>',
		Assign = '=',
		Access = '.',
		Type = ':',
		Optional = '?',
	};

	enum class Operator2 : u16
	{
		Or = '||',
		And = '&&',
		ShiftLeft = '<<',
		ShiftRight = '>>',
		AddAssign = '+=',
		SubtractAssign = '-=',
		MultiplyAssign = '*=',
		DivideAssign = '/=',
		ModuloAssign = '%=',
		BitwiseAndAssign = '&=',
		BitwiseOrAssign = '|=',
		BitwiseXorAssign = '^=',
		Return = '->',
		Equal = '==',
		NotEqual = '!=',
		LessThanOrEqual = '<=',
		GreaterThanOrEqual = '>='
	};
	enum class Keywords : u8
	{
		Template,
		Abstract,
		Statement,
		Group,
		Namespace,
		Rule,
		For,
		While,
		Loop,
		If,
		Else,
		ElseIf,
		Switch,
		Case,
		Default,
	};

	struct Template
	{
	};

	enum class Delimiter : u8
	{
		OpenBrace = '{',
		CloseBrace = '}',
		OpenParenthesis = '(',
		CloseParenthesis = ')',
		OpenSquareBracket = '[',
		CloseSquareBracket = ']',
	};

	enum class Punctuation : u8
	{
		Colon = ':',
		Semicolon = ';',
		Comma = ',',
	};
}
