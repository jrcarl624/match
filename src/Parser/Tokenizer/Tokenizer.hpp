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
	Token_e::Zero:\
	case Token_e::One:\
	case Token_e::Two:\
	case Token_e::Three:\
	case Token_e::Four:\
	case Token_e::Five:\
	case Token_e::Six:\
	case Token_e::Seven:\
	case Token_e::Eight:\
	case Token_e::Nine\

#define operator_1_no_divide_tokens \
	Token_e::Not:\
	case Token_e::Colon:\
	case Token_e::BitwiseOr:\
	case Token_e::BitwiseAnd:\
	case Token_e::BitwiseXor:\
	case Token_e::Add:\
	case Token_e::Assign:\
	case Token_e::Subtract:\
	case Token_e::Multiply:\
	case Token_e::Modulo:\
	case Token_e::EqualTo:\
	case Token_e::LessThan:\
	case Token_e::GreaterThan:\
	case Token_e::DotAccess:\
	case Token_e::Optional\
/*And = '&' + '&' + MAGIC_NUMBER,//76
		NotEqual = '!' + '=' + MAGIC_NUMBER,//94 
		ModuloAssign = '%' + '=' + MAGIC_NUMBER,//98 
		BitwiseAndAssign = '&' + '=' + MAGIC_NUMBER,//99 
		MultiplyAssign = '*' + '=' + MAGIC_NUMBER,//103 
		AddAssign = '+' + '=' + MAGIC_NUMBER,//104 
		SubtractAssign = '-' + '=' + MAGIC_NUMBER,//106 
		Return = '-' + '>' + MAGIC_NUMBER,//107 
		DivideAssign = '/' + '=' + MAGIC_NUMBER,//108 
		ScopeResolution = ':' + ':' + MAGIC_NUMBER,//116 
		ShiftLeft = '<' + '<' + MAGIC_NUMBER,//120 
		LessThanOrEqual = '<' + '=' + MAGIC_NUMBER,//121 
		EqualTo = '=' + '=' + MAGIC_NUMBER,//122 
		GreaterThanOrEqual = '>' + '=' + MAGIC_NUMBER,//123 
		ShiftRight = '>' + '>' + MAGIC_NUMBER,//124 
		BitwiseXorAssign = '^' + '=' + MAGIC_NUMBER,//155 
		BitwiseOrAssign = '|' + '=' + MAGIC_NUMBER,//185 
		Or = '|' + '|' + MAGIC_NUMBER,//248 */
#define operator_2_tokens \
		Token_e::And:\
		case Token_e::NotEqual:\
		case Token_e::ModuloAssign:\
		case Token_e::BitwiseAndAssign:\
		case Token_e::MultiplyAssign:\
		case Token_e::AddAssign:\
		case Token_e::SubtractAssign:\
		case Token_e::Return:\
		case Token_e::DivideAssign:\
		case Token_e::ScopeResolution:\
		case Token_e::ShiftLeft:\
		case Token_e::LessThanOrEqual:\
		case Token_e::EqualTo:\
		case Token_e::GreaterThanOrEqual:\
		case Token_e::ShiftRight:\
		case Token_e::BitwiseXorAssign:\
		case Token_e::BitwiseOrAssign:\
		case Token_e::Or\
		



#define delimiter_tokens \
	Token_e::OpenCurlyBracket:\
	case Token_e::CloseCurlyBracket:\
	case Token_e::OpenRoundBracket:\
	case Token_e::CloseRoundBracket:\
	case Token_e::OpenSquareBracket:\
	case Token_e::CloseSquareBracket:\
	case Token_e::Comma:\
	case Token_e::SemiColon\

#define quote_tokens \
	Token_e::StringLiteral:\
	case Token_e::CharLiteral\

#define uppercase_tokens \
	Token_e::Upper_A:\
	case Token_e::Upper_B:\
	case Token_e::Upper_C:\
	case Token_e::Upper_D:\
	case Token_e::Upper_E:\
	case Token_e::Upper_F:\
	case Token_e::Upper_G:\
	case Token_e::Upper_H:\
	case Token_e::Upper_I:\
	case Token_e::Upper_J:\
	case Token_e::Upper_K:\
	case Token_e::Upper_L:\
	case Token_e::Upper_M:\
	case Token_e::Upper_N:\
	case Token_e::Upper_O:\
	case Token_e::Upper_P:\
	case Token_e::Upper_Q:\
	case Token_e::Upper_R:\
	case Token_e::Upper_S:\
	case Token_e::Upper_T:\
	case Token_e::Upper_U:\
	case Token_e::Upper_V:\
	case Token_e::Upper_W:\
	case Token_e::Upper_X:\
	case Token_e::Upper_Y:\
	case Token_e::Upper_Z\

#define lowercase_tokens \
	Token_e::Lower_A:\
	case Token_e::Lower_B:\
	case Token_e::Lower_C:\
	case Token_e::Lower_D:\
	case Token_e::Lower_E:\
	case Token_e::Lower_F:\
	case Token_e::Lower_G:\
	case Token_e::Lower_H:\
	case Token_e::Lower_I:\
	case Token_e::Lower_J:\
	case Token_e::Lower_K:\
	case Token_e::Lower_L:\
	case Token_e::Lower_M:\
	case Token_e::Lower_N:\
	case Token_e::Lower_O:\
	case Token_e::Lower_P:\
	case Token_e::Lower_Q:\
	case Token_e::Lower_R:\
	case Token_e::Lower_S:\
	case Token_e::Lower_T:\
	case Token_e::Lower_U:\
	case Token_e::Lower_V:\
	case Token_e::Lower_W:\
	case Token_e::Lower_X:\
	case Token_e::Lower_Y:\
	case Token_e::Lower_Z\

#define horizontal_whitespace_tokens \
	Token_e::CarriageReturn:\
	case Token_e::FormFeed:\
	case Token_e::Space:\
	case Token_e::Tab\

namespace match::parser {

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
			this->currentType = static_cast<Token_e>(byte);
		}

		inline void SetTokenType(Token_e type) {
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
		Token_e currentType = Token_e::Invalid;
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
