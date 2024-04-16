#include "Tokeniser.hpp"
#include <cstdint>
#include "Token.hpp"

#define fun() {}
namespace Match::Parser
{
	Tokeniser::Tokeniser()
	{
	}
	Tokeniser::~Tokeniser()
	{
	}

	enum class Operator : u16
	{
		// Arithmetic

	};

	void Tokeniser::Tokenise(const SlideViewChar source)
	{
		while (true)
		{
			u8 peek = this->m_window.Peak<u8>();
			// Peak the tail of the window
			switch (peek)
			{
			case (u8)Whitespace::CarriageReturn:
			case (u8)Whitespace::FormFeed:
			case (u8)Whitespace::Newline:
			case (u8)Whitespace::Space:
			case (u8)Whitespace::Tab:
			{
				this->m_window.Skip();

				if (peek == (u8)Whitespace::Newline)
				{
					this->IncrementRow();
				}
			}

				// operators

			case (u8)Delimiters::OpenBrace:
			case (u8)Delimiters::CloseBrace:
			case (u8)Delimiters::OpenParenthesis:
			case (u8)Delimiters::CloseParenthesis:
			case (u8)Delimiters::OpenSquareBracket:
			case (u8)Delimiters::CloseSquareBracket:
			{
			}
			}
		}
	}
