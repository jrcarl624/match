#pragma once
#include "../../Types/SlideView.hpp"


namespace Match::Parser {
	constexpr u8 MAGIC_NUMBER = 37;


	enum class Token_E :u8 {

				// Primitives
		Char = 1,
		U32 = 2,
		I32 = 4,
		F32 = 5,
		String = 6,
		U64 = 7,
		I64 = 8,
		Bool = 14,

		// Comments
		Comment = 15,

		// Identifier
		Identifier = 16,

		// End of file
		Eof = 3,

		// Unknown
		Invalid = 17,

		// Literals
		BoolLiteral = 18,
		NumericLiteral = 19,
		CharLiteral = '\'', //39
		StringLiteral = '"', //34


			// Switch='s',
			// Case='c',
			// Default='d',



		Not = '!', //33
		Modulo = '%', //37
		BitwiseAnd = '&', //38

		// Brackets ----------------------
		CloseRoundBracket = ')', //41
		OpenRoundBracket = '(', //40

		Multiply = '*', //42
		Add = '+', //43
		Subtract = '-', //45
		Access = '.', //46
		Divide = '/', //47
		Colon = ':', //58
		LessThan = '<', //60
		Assign = '=', // 61
		GreaterThan = '>', // 62
		Optional = '?', // 63
		BitwiseXor = '^', // 94
		BitwiseOr = '|', //124

		And = '&' + '&' + MAGIC_NUMBER,//76
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
		Or = '|' + '|' + MAGIC_NUMBER,//248 

		// todo add left and right shift assign
		// Keywords
		Abstract = 'a', // 97
		Else = 'e', //101
		For = 'f', //102
		Group = 'g', //103
		If = 'i', //105
		Loop = 'l', //108
		Match = 'm', //109
		Pattern = 'p', //112
		Rule = 'r', //114
		Statement = 's', //115
		Template = 't', //116
		Namespace = 'n', //110
		While = 'w', //119

		OpenSquareBracket = '[', //91 
		CloseSquareBracket = ']', //93

		OpenCurlyBracket = '{', //123
		CloseCurlyBracket = '}', //125

		// Punctuation
		Comma = ',', //44
		SemiColon = ';', //59
		Underscore = '_', //95




		// PARSING ONLY........

		// Whitespace
		Tab = '\t',
		FormFeed = '\x0C',
		CarriageReturn = '\r',
		Space = ' ',
		Null = '\0',
		Newline = '\n',

		// Numbers 
		Zero = '0',
		One = '1',
		Two = '2',
		Three = '3',
		Four = '4',
		Five = '5',
		Six = '6',
		Seven = '7',
		Eight = '8',
		Nine = '9',

		// Letters
		Lower_A = 'a', //97
		Lower_B = 'b', //98
		Lower_C = 'c', //99
		Lower_D = 'd', //100
		Lower_E = 'e', //101
		Lower_F = 'f', //102
		Lower_G = 'g', //103
		Lower_H = 'h', //104
		Lower_I = 'i', //105
		Lower_J = 'j', //106
		Lower_K = 'k', //107
		Lower_L = 'l', //108
		Lower_M = 'm', //109
		Lower_N = 'n', //110
		Lower_O = 'o', //111
		Lower_P = 'p', //112
		Lower_Q = 'q', //113
		Lower_R = 'r', //114
		Lower_S = 's', //115
		Lower_T = 't', //116
		Lower_U = 'u', //117
		Lower_V = 'v', //118
		Lower_W = 'w', //119
		Lower_X = 'x', //120
		Lower_Y = 'y', //121
		Lower_Z = 'z', //122

		Upper_A = 'A', //65
		Upper_B = 'B', //66
		Upper_C = 'C', //67
		Upper_D = 'D', //68
		Upper_E = 'E', //69
		Upper_F = 'F', //70
		Upper_G = 'G', //71
		Upper_H = 'H', //72
		Upper_I = 'I', //73
		Upper_J = 'J', //74
		Upper_K = 'K', //75
		Upper_L = 'L', //76
		Upper_M = 'M', //77
		Upper_N = 'N', //78
		Upper_O = 'O', //79
		Upper_P = 'P', //80
		Upper_Q = 'Q', //81
		Upper_R = 'R', //82
		Upper_S = 'S', //83
		Upper_T = 'T', //84
		Upper_U = 'U', //85
		Upper_V = 'V', //86
		Upper_W = 'W', //87
		Upper_X = 'X', //88
		Upper_Y = 'Y', //89
		Upper_Z = 'Z', //90
		

	};

	class Token {
		public:
		Token(SlideView<u8> subTokens, u64 column, u64 row, Token_E type) : m_subTokens(subTokens), m_column(column), m_row(row), m_type(type) {}
		Token() {}
		~Token() {}

		SlideView<u8> GetSubTokens() const { return m_subTokens; }

			//std::string_view GetSubTokensAsStr() { return m_subTokens.ToString<char>(); }

		u64 GetColumn() const { return m_column; }
		u64 GetRow() const { return m_row; }
		u64 Length() const { return m_subTokens.Size(); }
		Token_E GetType() const { return m_type; }
		void SetSubTokens(SlideView<u8> subTokens) { m_subTokens = subTokens; }
		void SetColumn(u64 column) { m_column = column; }
		void SetRow(u64 row) { m_row = row; }

		inline std::string ToString() {
			std::string str = "Token: ";

			switch (m_type) {
				case Token_E::BoolLiteral:
					str += "BoolLiteral";
					break;
				case Token_E::NumericLiteral:
					str += "NumericLiteral";
					break;
				case Token_E::CharLiteral:
					str += "CharLiteral";
					break;
				case Token_E::StringLiteral:
					str += "StringLiteral";
					break;
				case Token_E::Pattern:
					str += "Pattern";
					break;
				case Token_E::Template:
					str += "Template";
					break;
				case Token_E::Abstract:
					str += "Abstract";
					break;
				case Token_E::Statement:
					str += "Statement";
					break;
				case Token_E::Group:
					str += "Group";
					break;
				case Token_E::Namespace:
					str += "Namespace";
					break;
				case Token_E::Rule:
					str += "Rule";
					break;
				case Token_E::For:
					str += "For";
					break;
				case Token_E::While:
					str += "While";
					break;
				case Token_E::Loop:
					str += "Loop";
					break;
				case Token_E::If:
					str += "If";
					break;
				case Token_E::Else:
					str += "Else";
					break;
				case Token_E::Match:
					str += "Match";
					break;
				case Token_E::ScopeResolution:
					str += "ScopeResolution";
					break;
				case Token_E::BitwiseOr:
					str += "BitwiseOr";
					break;
				case Token_E::Or:
					str += "Or";
					break;
				case Token_E::BitwiseAnd:
					str += "BitwiseAnd";
					break;
				case Token_E::And:
					str += "And";
					break;
				case Token_E::BitwiseXor:
					str += "BitwiseXor";
					break;
				case Token_E::Not:
					str += "Not";
					break;
				case Token_E::ShiftLeft:
					str += "ShiftLeft";
					break;
				case Token_E::ShiftRight:
					str += "ShiftRight";
					break;
				case Token_E::Add:
					str += "Add";
					break;
				case Token_E::Subtract:
					str += "Subtract";
					break;
				case Token_E::Multiply:
					str += "Multiply";
					break;
				case Token_E::Divide:
					str += "Divide";
					break;
				case Token_E::Modulo:
					str += "Modulo";
					break;
				case Token_E::EqualTo:
					str += "EqualTo";
					break;
				case Token_E::NotEqual:
					str += "NotEqual";
					break;
				case Token_E::LessThan:
					str += "LessThan";
					break;
				case Token_E::GreaterThan:
					str += "GreaterThan";
					break;
				case Token_E::LessThanOrEqual:
					str += "LessThanOrEqual";
					break;
				case Token_E::GreaterThanOrEqual:
					str += "GreaterThanOrEqual";
					break;
				case Token_E::Assign:
					str += "Assign";
					break;
				case Token_E::Access:
					str += "Access";
					break;
				case Token_E::Colon:
					str += "TypeDefinition";
					break;
				case Token_E::Optional:
					str += "Optional";
					break;
				case Token_E::Return:
					str += "Return";
					break;
				case Token_E::AddAssign:
					str += "AddAssign";
					break;
				case Token_E::SubtractAssign:
					str += "SubtractAssign";
					break;
				case Token_E::MultiplyAssign:
					str += "MultiplyAssign";
					break;
				case Token_E::DivideAssign:
					str += "DivideAssign";
					break;
				case Token_E::ModuloAssign:
					str += "ModuleloAssign";
					break;
				case Token_E::BitwiseXorAssign:
					str += "BitwiseXorAssign";
					break;
				case Token_E::BitwiseAndAssign:
					str += "BitwiseAndAssign";
					break;
				case Token_E::BitwiseOrAssign:
					str += "BitwiseOrAssign";
					break;
				
				case Token_E::OpenCurlyBracket:
					str += "OpenCurlyBracket";
					break;
				case Token_E::CloseCurlyBracket:
					str += "CloseCurlyBracket";
					break;
				case Token_E::OpenSquareBracket:
					str += "OpenSquareBracket";
					break;
				case Token_E::CloseSquareBracket:
					str += "CloseSquareBracket";
					break;
				case Token_E::OpenRoundBracket:
					str += "OpenRoundBracket";
					break;
				case Token_E::CloseRoundBracket:
					str += "CloseRoundBracket";
					break;
				case Token_E::Comma:
					str += "Comma";
					break;
				
				case Token_E::SemiColon:
					str += "SemiColon";
					break;
				case Token_E::Comment:
					str += "Comment";
					break;
				case Token_E::Identifier:
					str += "Identifier";
					break;
				case Token_E::Eof:
					str += "Eof";
					break;
				default:
					str += "Invalid token";
					break;

			}




			//str += " ";
			//str += m_subTokens.ToString<char>();
			return str;
		}

		private:
		SlideView<u8> m_subTokens = {};
		u64 m_column = 0;
		u64 m_row = 0;
		Token_E m_type = Token_E::Invalid;
	};

}