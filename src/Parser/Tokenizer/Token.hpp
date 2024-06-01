#pragma once
#include "../../Types/SlideView.hpp"

#pragma warning(disable: 4369)
namespace match::parser {
	// Please for the love of god don't change this value.
	// Yes this means if ur rewriting this codebase you must keep this unless you change how we parse.
	constexpr u8 MAGIC_NUMBER = 37;


	enum class Token_e :u8 {

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
		IntegerLiteral = 19,
		FloatLiteral = 20,
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
		DotAccess = '.', //46
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

		OpenAngleBracket = '<', 
		CloseAngleBracket = '>',

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
		Token(SlideView<u8> subTokens, u64 column, u64 row, Token_e type) : m_subTokens(subTokens), m_column(column), m_row(row), m_type(type) {}
		Token() {}
		~Token() {}

		SlideView<u8> GetSubTokens() const { return m_subTokens; }

		std::string_view GetSubTokensAsStr() { return m_subTokens; }

		u64 GetColumn() const { return m_column; }
		u64 GetRow() const { return m_row; }
		u64 Length() const { return m_subTokens.Size(); }
		Token_e GetType() const { return m_type; }
		void SetSubTokens(SlideView<u8> subTokens) { m_subTokens = subTokens; }
		void SetColumn(u64 column) { m_column = column; }
		void SetRow(u64 row) { m_row = row; }

		inline std::string ToString() {
			switch (m_type) {

				case Token_e::BoolLiteral:
					return "BoolLiteral";
				case Token_e::IntegerLiteral:
					return "NumericLiteral";
				case Token_e::CharLiteral:
					return "CharLiteral";
				case Token_e::StringLiteral:
					return "StringLiteral";
				case Token_e::Pattern:
					return "Pattern";
				case Token_e::Template:
					return "Template";
				case Token_e::Abstract:
					return "Abstract";
				case Token_e::Statement:
					return "Statement";
				case Token_e::Group:
					return "Group";
				case Token_e::Namespace:
					return "Namespace";
				case Token_e::Rule:
					return "Rule";
				case Token_e::For:
					return "For";
				case Token_e::While:
					return "While";
				case Token_e::Loop:
					return "Loop";
				case Token_e::If:
					return "If";
				case Token_e::Else:
					return "Else";
				case Token_e::Match:
					return "Match";
				case Token_e::ScopeResolution:
					return "ScopeResolution";
				case Token_e::BitwiseOr:
					return "BitwiseOr";
				case Token_e::Or:
					return "Or";
				case Token_e::BitwiseAnd:
					return "BitwiseAnd";
				case Token_e::And:
					return "And";
				case Token_e::BitwiseXor:
					return "BitwiseXor";
				case Token_e::Not:
					return "Not";
				case Token_e::ShiftLeft:
					return "ShiftLeft";
				case Token_e::ShiftRight:
					return "ShiftRight";
				case Token_e::Add:
					return "Add";
				case Token_e::Subtract:
					return "Subtract";
				case Token_e::Multiply:
					return "Multiply";
				case Token_e::Divide:
					return "Divide";
				case Token_e::Modulo:
					return "Modulo";
				case Token_e::EqualTo:
					return "EqualTo";
				case Token_e::NotEqual:
					return "NotEqual";
				case Token_e::LessThan:
					return "LessThan";
				case Token_e::GreaterThan:
					return "GreaterThan";
				case Token_e::LessThanOrEqual:
					return "LessThanOrEqual";
				case Token_e::GreaterThanOrEqual:
					return "GreaterThanOrEqual";
				case Token_e::Assign:
					return "Assign";
				case Token_e::DotAccess:
					return "Access";
				case Token_e::Colon:
					return "TypeDefinition";
				case Token_e::Optional:
					return "Optional";
				case Token_e::Return:
					return "Return";
				case Token_e::AddAssign:
					return "AddAssign";
				case Token_e::SubtractAssign:
					return "SubtractAssign";
				case Token_e::MultiplyAssign:
					return "MultiplyAssign";
				case Token_e::DivideAssign:
					return "DivideAssign";
				case Token_e::ModuloAssign:
					return "ModuleloAssign";
				case Token_e::BitwiseXorAssign:
					return "BitwiseXorAssign";
				case Token_e::BitwiseAndAssign:
					return "BitwiseAndAssign";
				case Token_e::BitwiseOrAssign:
					return "BitwiseOrAssign";
				case Token_e::OpenCurlyBracket:
					return "OpenCurlyBracket";
				case Token_e::CloseCurlyBracket:
					return "CloseCurlyBracket";
				case Token_e::OpenSquareBracket:
					return "OpenSquareBracket";
				case Token_e::CloseSquareBracket:
					return "CloseSquareBracket";
				case Token_e::OpenRoundBracket:
					return "OpenRoundBracket";
				case Token_e::CloseRoundBracket:
					return "CloseRoundBracket";
				case Token_e::Comma:
					return "Comma";
				case Token_e::SemiColon:
					return "SemiColon";
				case Token_e::Underscore:
					return "Underscore";
				case Token_e::Comment:
					return "Comment";
				case Token_e::Identifier:
					return "Identifier";
				case Token_e::Eof:
					return "Eof";
				case Token_e::Invalid:
					return "Invalid";

			}
		}

		private:
		SlideView<u8> m_subTokens = {};
		u64 m_column = 0;
		u64 m_row = 0;
		Token_e m_type = Token_e::Invalid;
	};

}
#pragma warning(default: 4369)