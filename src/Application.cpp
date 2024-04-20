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
        const char* testCode = R"( // Numeric Literals -----------------------
            case Token_E::Zero:
            case Token_E::One:
            case Token_E::Two:
            case Token_E::Three:
            case Token_E::Four:
            case Token_E::Five:
            case Token_E::Six:
            case Token_E::Seven:
            case Token_E::Eight:
            case Token_E::Nine: {
                    this->SetTokenType(Token_E::NumericLiteral);
                number:
                    switch (this->SetCurrentPushBack<Token_E>()) {
                        case Token_E::Zero:
                        case Token_E::One:
                        case Token_E::Two:
                        case Token_E::Three:
                        case Token_E::Four:
                        case Token_E::Five:
                        case Token_E::Six:
                        case Token_E::Seven:
                        case Token_E::Eight:
                        case Token_E::Nine:
                        case Token_E::Underscore: // I am not sure about this one...
                            this->m_subTokens.IsSubViewInBounds(m_window);
                            goto number;
                        default:
                            if (this->m_window.Back<u8>() == '.')";

        Parser::Lexer tokenizer;
        SlideView<u8> source = SlideView<u8>(testCode);
        auto Tokens = tokenizer.Lex(source);

       
        auto r = true;
    }
}