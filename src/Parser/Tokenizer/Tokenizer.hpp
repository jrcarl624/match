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

	class Lexer {
		public:
		Lexer();
		~Lexer();

		std::vector<Token> Lex(SlideView<u8> source);

		inline Token NextToken();

		inline void IncrementRow() {
			this->lastRowIndex = this->m_subTokens.IndexOf(this->m_window.GetHead()) - this->m_window.Size();
			this->row++;
		}

		inline void SetTokenType(u8 byte) {
			this->currentType = static_cast<Token_E>(byte);
		}

		inline void SetTokenType(Token_E type) {
			this->currentType = type;
		}

		template <typename T>
		inline T SetCurrentPushBack() {
			return static_cast<T>(this->current = this->m_window.PushBack<u8>());
		}


		private:
		SlideView<u8> m_subTokens = {};
		SlideView<u8> m_window = {};
		u64 row = 0;
		u64 lastRowIndex = 0;
		Token_E currentType = Token_E::Invalid;
		u8 current = '\0';
		u8 next = '\0';
		u8 quote = '\0';
		u8 commentLevel;
		bool incomplete = false;
	};






	enum Comment_E : u16 {
		SingleLine = swapEndian('//'),
		MultiLineStart = swapEndian('/*'),
		MultiLineEnd = swapEndian('*/'),
	};


	// struct Template
	// {
	// };
}
