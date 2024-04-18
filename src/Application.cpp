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

        Parser::Tokenizer tokenizer;
        SlideView<u8> source = SlideView<u8>("fn=== main() {\nprint!(\"Hello,\nworld!\");\"Hello; \" world!\"\nif \"true\" != false {let xyz_99_yoMama = 5 | \"some\" | 'c' | 's';}}\"2");
        auto Tokens = tokenizer.Tokenize(source);
        for (auto& token : Tokens)
            LoggerInstance.Log("Token Of Type: {}", LogLevel::LOG_DEBUG, token.ToString());

    }
}