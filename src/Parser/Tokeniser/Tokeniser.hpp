#pragma once
#include <string>
#include "TokenTypes.hpp"
#include "../../types.hpp"
#include "../../Types/SlideView.hpp"
#include "../../Types/RangeGeneration.hpp"

namespace Match::Parser
{
	class Tokeniser
	{
	public:
		Tokeniser();
		~Tokeniser();

	public:
		void Tokenise(const SlideViewChar source);

		/*

	uppercase: b'A'..=b'Z',
	lowercase: b'a'..=b'z',
	numeric: b'0'..=b'9',*/

	private:
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
		const u8 scopeSeparator = ';';
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

		enum class Operators1 : u8
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

		enum class Operators2 : u16
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
			Access = '.',
			Assign = '=',
			Equal = '==',
			NotEqual = '!=',
			LessThanOrEqual = '<=',
			GreaterThanOrEqual = '>=',
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

		inline void IncrementRow()
		{
			this->lastRowIndex = this->m_subTokens.indexOf(this->m_window.getHeadPtr()) - this->m_window.Size();
			this->row++;
		}

	private:
		SlideViewChar m_subTokens = {};
		SlideViewChar m_window = {};
		uSize row = 0;
		uSize lastRowIndex = 0;
	};
}
