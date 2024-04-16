#pragma once
#include "Tokeniser.hpp"
#include <string>

namespace Match
{
	class Parser
	{
	public:
		Parser(std::string_view code);
		~Parser();
	private:
		Tokeniser tokeniser;
	};
}

