#pragma once
#include <string>
#include "TokenTypes.hpp"
#include "../../types.hpp"
#include "../../Types/SlideView.hpp"
#include "../../Types/RangeGeneration.hpp"
#include "Token.hpp"
#include <bit>
#include <vector>
#define numeric_tokens \
	Token_E::Zero:\
	case Token_E::One:\
	case Token_E::Two:\
	case Token_E::Three:\
	case Token_E::Four:\
	case Token_E::Five:\
	case Token_E::Six:\
	case Token_E::Seven:\
	case Token_E::Eight:\
	case Token_E::Nine\

#define operator_1_no_divide_tokens \
	Token_E::Not:\
	case Token_E::BitwiseOr:\
	case Token_E::BitwiseAnd:\
	case Token_E::BitwiseXor:\
	case Token_E::Add:\
	case Token_E::Assign:\
	case Token_E::Subtract:\
	case Token_E::Multiply:\
	case Token_E::Modulo:\
	case Token_E::EqualTo:\
	case Token_E::LessThan:\
	case Token_E::GreaterThan:\
	case Token_E::DotAccess:\
	case Token_E::Optional:\
	case Token_E::Colon\

#define operator_2nd_half_tokens \
	Token_E::BitwiseAnd: \
	case Token_E::BitwiseOr:\
	case Token_E::Assign: \
	case Token_E::GreaterThan: \
	case Token_E::LessThan: \
	case Token_E::Colon \


#define delimiter_tokens \
	Token_E::OpenCurlyBracket:\
	case Token_E::CloseCurlyBracket:\
	case Token_E::OpenRoundBracket:\
	case Token_E::CloseRoundBracket:\
	case Token_E::OpenSquareBracket:\
	case Token_E::CloseSquareBracket:\
	case Token_E::Comma:\
	case Token_E::SemiColon\

#define quote_tokens \
	Token_E::StringLiteral:\
	case Token_E::CharLiteral\

#define uppercase_tokens \
	Token_E::Upper_A:\
	case Token_E::Upper_B:\
	case Token_E::Upper_C:\
	case Token_E::Upper_D:\
	case Token_E::Upper_E:\
	case Token_E::Upper_F:\
	case Token_E::Upper_G:\
	case Token_E::Upper_H:\
	case Token_E::Upper_I:\
	case Token_E::Upper_J:\
	case Token_E::Upper_K:\
	case Token_E::Upper_L:\
	case Token_E::Upper_M:\
	case Token_E::Upper_N:\
	case Token_E::Upper_O:\
	case Token_E::Upper_P:\
	case Token_E::Upper_Q:\
	case Token_E::Upper_R:\
	case Token_E::Upper_S:\
	case Token_E::Upper_T:\
	case Token_E::Upper_U:\
	case Token_E::Upper_V:\
	case Token_E::Upper_W:\
	case Token_E::Upper_X:\
	case Token_E::Upper_Y:\
	case Token_E::Upper_Z\

#define lowercase_tokens \
	Token_E::Lower_A:\
	case Token_E::Lower_B:\
	case Token_E::Lower_C:\
	case Token_E::Lower_D:\
	case Token_E::Lower_E:\
	case Token_E::Lower_F:\
	case Token_E::Lower_G:\
	case Token_E::Lower_H:\
	case Token_E::Lower_I:\
	case Token_E::Lower_J:\
	case Token_E::Lower_K:\
	case Token_E::Lower_L:\
	case Token_E::Lower_M:\
	case Token_E::Lower_N:\
	case Token_E::Lower_O:\
	case Token_E::Lower_P:\
	case Token_E::Lower_Q:\
	case Token_E::Lower_R:\
	case Token_E::Lower_S:\
	case Token_E::Lower_T:\
	case Token_E::Lower_U:\
	case Token_E::Lower_V:\
	case Token_E::Lower_W:\
	case Token_E::Lower_X:\
	case Token_E::Lower_Y:\
	case Token_E::Lower_Z\

#define horizontal_whitespace_tokens \
	Token_E::CarriageReturn:\
	case Token_E::FormFeed:\
	case Token_E::Space:\
	case Token_E::Tab\

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
		u16 commentLevel = 0;
		bool incomplete = false;
	};
	enum Comment_E : u16 {
		SingleLine = '//',
		MultiLineStart = std::byteswap<u16>('/*'),
		MultiLineEnd = std::byteswap<u16>('*/'),
	};

}
