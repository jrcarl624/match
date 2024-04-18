#pragma once
#include <string>
#include "TokenTypes.hpp"
#include "../../types.hpp"
#include "../../Types/SlideView.hpp"
#include "../../Types/RangeGeneration.hpp"
#include "Token.hpp"
#include <vector>

// ((val & 0xFF00) >> 8) | ((val & 0x00FF) << 8)
#define swapEndian(shor) ((shor & 0xFF00) >> 8) | ((shor & 0x00FF) << 8)

namespace Match::Parser {

	class Tokenizer {
	public:
		Tokenizer();
		~Tokenizer();

		std::vector<Token> Tokenize(SlideView<u8> source);

		inline Token NextToken();

		inline void IncrementRow() {
			this->lastRowIndex = this->m_subTokens.IndexOf(this->m_window.GetHead()) - this->m_window.Size();
			this->row++;
		}

		inline void SetTokenType(Token_E type) {
			this->currentType = type;
		}

	private:
		SlideView<u8> m_subTokens = {};
		SlideView<u8> m_window = {};
		u64 row = 0;
		u64 lastRowIndex = 0;
		Token_E currentType = Token_E::Unknown;
	};

	enum class Delimiter_E : u8 {
		OpenBrace = '{',
		CloseBrace = '}',
		OpenParenthesis = '(',
		CloseParenthesis = ')',
		OpenSquareBracket = '[',
		CloseSquareBracket = ']',
		TypeSeparator = ':',
		ListSeparator = ',',
	};

	enum class Whitespace_E : u8 {
		Tab = '\t',
		FormFeed = '\x0C',
		CarriageReturn = '\r',
		Space = ' ',
		Newline = '\n'
	};

	enum class QuotePrefix : u8 {
		Raw = 'r',
		Binary = 'b',
		Unicode = 'u',
		Formatted = 'f'
	};

	enum class Quote_E : u8 {
		Single = '\'',
		Double = '"'
	};

	enum class OperatorOne_E : u8 {
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
		Access = '.',
		Optional = '?',
	};

	enum class OperatorTwo_E : u16 {
		Or = swapEndian('||'),
		And = swapEndian('&&'),
		ShiftLeft = swapEndian('<<'),
		ShiftRight = swapEndian('>>'),
		AddAssign = swapEndian('+='),
		SubtractAssign = swapEndian('-='),
		MultiplyAssign = swapEndian('*='),
		DivideAssign = swapEndian('/='),
		ModuloAssign = swapEndian('%='),
		BitwiseAndAssign = swapEndian('&='),
		BitwiseOrAssign = swapEndian('|='),
		BitwiseXorAssign = swapEndian('^='),
		Return = swapEndian('->'),
		Equal = swapEndian('=='),
		NotEqual = swapEndian('!='),
		LessThanOrEqual = swapEndian('<='),
		GreaterThanOrEqual = swapEndian('>='),
		ScopeResolution = swapEndian('::'),
	};

	enum Comment_E : u16 {
		SingleLine = swapEndian('//'),
		MultiLineStart = swapEndian('/*'),
		MultiLineEnd = swapEndian('*/'),
	};

	enum class Keyword_E : u8 {
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

	// struct Template
	// {
	// };
}
