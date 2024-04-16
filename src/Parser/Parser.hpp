#pragma once
#include "Tokeniser.hpp"
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

