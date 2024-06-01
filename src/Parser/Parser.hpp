#pragma once
#include "Tokenizer/Tokenizer.hpp"
#include <string>

namespace match::parser {
	class Parser {
	public:
		Parser();
		~Parser();
	private:
	Lexer Tokenizer;
	};
}

