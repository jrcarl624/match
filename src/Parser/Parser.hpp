#pragma once
#include "Tokeniser/Tokeniser.hpp"
#include <string>

namespace Match::Parser
{
	class Parser
	{
	public:
		Parser();
		~Parser();
	private:
		Tokeniser tokeniser;
	};
}

