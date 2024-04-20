#include "Application.hpp"
#include "Logs/Logs.hpp"
#include "Parser/Tokenizer/Tokenizer.hpp"
namespace Match {
    Application::Application() {
        run();
    }

    Application::~Application() {

    }

    void Application::run() {
        const char* testCode = R"({])";

        Parser::Lexer tokenizer;
        SlideView<u8> source = SlideView<u8>(testCode);
        auto Tokens = tokenizer.Lex(source);
        //for (auto& token : Tokens)
       
        auto r = true;
    }
}