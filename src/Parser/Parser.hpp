#pragma once
#include "Tokenizer/Tokenizer.hpp"
#include <string>

namespace Match::Parser {
	class Parser {
	public:
		Parser();
		~Parser();
	private:
	Lexer Tokenizer;
	};
}

