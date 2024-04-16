#pragma once
#include <string>
#include "TokenTypes.hpp"
#include "../types.hpp"
#include "SlideView.hpp"

namespace Match::Parser
{
	class Tokeniser
	{	
	public:
		Tokeniser();
		~Tokeniser();
	public:
		void Tokenise(const SlideViewChar source);
	private:

	private:
		SlideViewChar m_subTokens = {};
		SlideViewChar m_source = {};
        SlideViewChar m_sourceView = {};
		uSize row = 0;
		uSize lastRowIndex = 0; 
	};
}
