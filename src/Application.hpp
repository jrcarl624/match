#pragma once
#include "Parser/Parser.hpp"


namespace Match
{
    class Application
    {
    public:
        Application();
        ~Application();
    private:
        void run();
    private:
        Parser::Parser parser;

    };

}