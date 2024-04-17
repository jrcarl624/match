#pragma once
#include <string>
#include "TokenTypes.hpp"
#include "../../types.hpp"
#include "../../Types/SlideView.hpp"
#include "../../Types/RangeGeneration.hpp"
#include "Token.hpp"


#define getFirstByte(shor) (static_cast<u8>(shor >> 8))

namespace Match::Parser
{

	class Tokenizer
	{
	public:
		Tokenizer();
		~Tokenizer();

	public:
		inline Token NextToken();

		inline void IncrementRow()
		{
			this->lastRowIndex = this->m_subTokens.IndexOf(this->m_window.GetHeadPtr()) - this->m_window.Size();
			this->row++;
		}

		inline void SetTokenType(TokenType type)
		{
			this->currentType = type;
		}
		/*
	/// Creates a new token from the current window
	#[inline(always)]
	fn create_next_token(&mut self) -> Token<'cxx> {
		//dbg!((self.window_head_index(), self.last_row_index));

		let token = Token::new(
			self.window(),
			self.row,
			self.window_head_index() - self.last_row_index,
		);

		self.window_head_reset();
		token
	}*/

		inline Token CreateToken()
		{

			Token token(this->m_window, reinterpret_cast<uSize>(this->m_window.GetHeadPtr() - this->lastRowIndex), this->row, this->currentType);
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

	const u8 listSeparator = ',';
	const u8 scopeResolution = ';';
	const u8 typeSeparator = ':';
	const u8 newLine = '\n';

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

	const u8 stringQuotes = '"';
	const u8 charQuotes = '\'';
	const u8 backslash = '\\';

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
