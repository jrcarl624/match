#pragma once
#include "Parser/Parser.hpp"
#include "Parser/Tokenizer/Token.hpp"


namespace match {
    class Application {
    public:
        Application();
        ~Application();
    private:
        void run();
    private:
        parser::Parser parser;

    };

}