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
		void Tokenise(const std::string_view source);
	private:

	private:
		std::string_view m_subTokens = {};
		std::string_view m_source = {};
        std::string_view m_sourceView = {};
		uSize row = 0;
		uSize lastRowIndex = 0; 
	};
}
