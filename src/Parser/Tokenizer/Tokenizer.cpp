#include "Tokenizer.hpp"
#include <cstdint>
#include "../../Types/SlideView.hpp"
#include "../../Logs/Logs.hpp"
namespace Match::Parser {
    Lexer::Lexer() {
    }
    Lexer::~Lexer() {
    }

    std::vector<Token> Lexer::Lex(SlideView<u8> source) {
        std::vector<Token> tokens = {};
        this->m_subTokens = source;
        this->m_window = this->m_subTokens.SubView();
        this->lastRowIndex = 0;

        while (this->m_subTokens.IsSubViewInBounds(m_window)) {
            Token token = this->NextToken();
            LoggerInstance.Log("{}", LogLevel::LOG_DEBUG, std::format("Token Of Type {} Found! Token Value: {}", token.ToString(), token.GetSubTokensAsStr()));
            tokens.push_back(token);
        };
        return tokens;
    }


    Token Lexer::NextToken() {
        this -> next = 0;
        this->quote = 0;
    next_sub_token:
        this->current = this->m_window.Back();

        switch (static_cast<Token_E>(this->current)) {

            // Whitespace -----------------------
            case Token_E::Newline:
                this->IncrementRow();
            case Token_E::CarriageReturn:
            case Token_E::FormFeed:
            case Token_E::Space:
            case Token_E::Tab:
                this->m_window.SkipTail();
                goto next_sub_token;

        // Operators -----------------------
            case Token_E::Divide:

                // Comments -----------------------
                switch (this->SetCurrentPushBack<u8>()) {
                    case static_cast<u8>(Comment_E::MultiLineStart):
                        this->SetTokenType(Token_E::Comment);
                        while (this->m_window.PushBack<Token_E>() != Token_E::Newline);
                        goto increment_and_return;
                    case static_cast<u8>(Comment_E::MultiLineEnd): {
                        this->SetTokenType(Token_E::Comment);
                        commentLevel = 1;
                        do {
                            // test an offset of 1
                            switch (this->m_window.PushBack<Comment_E>(1)) {
                                case Comment_E::MultiLineStart:
                                    commentLevel++;
                                    break;
                                case Comment_E::MultiLineEnd:
                                    commentLevel--;
                                    break;
                            }
                        } while (commentLevel);
                        this->m_window.IncTail();
                        goto increment_and_return;
                    }
                };
            case Token_E::Not:
            case Token_E::BitwiseOr:
            case Token_E::BitwiseAnd:
            case Token_E::BitwiseXor:
            case Token_E::Add:
            case Token_E::Assign:
            case Token_E::Subtract:
            case Token_E::Multiply:
            case Token_E::Modulo:
            case Token_E::EqualTo:
            case Token_E::LessThan:
            case Token_E::GreaterThan:
            case Token_E::Access:
            case Token_E::Optional:
            case Token_E::Colon: {
                    this->next = this->m_window.Back<u8>(1);
                    switch (static_cast<Token_E>(next)) {
                        case Token_E::BitwiseOr:
                        case Token_E::BitwiseAnd:
                        case Token_E::Assign:
                        case Token_E::GreaterThan:
                        case Token_E::LessThan:
                        case Token_E::Colon:
                            {
                                this->SetTokenType(this->current + next + MAGIC_NUMBER);
                                this->m_window.IncTail(1);
                                goto increment_and_return;
                            }
                    }
                    this->SetTokenType(this->current);

                    goto increment_and_return;
                }

            // Delimiters -----------------------
            case Token_E::OpenCurlyBracket:
            case Token_E::CloseCurlyBracket:
            case Token_E::OpenRoundBracket:
            case Token_E::CloseRoundBracket:
            case Token_E::OpenSquareBracket:
            case Token_E::CloseSquareBracket:
            case Token_E::Comma:
            case Token_E::SemiColon: {
                    this->SetTokenType(this->current);

                    // breaks nested switch in loop
                    if (this->m_window.IsPopulated())
                        this->m_window.IncTail();
                    goto increment_and_return;
                };
            // Quotes -----------------------
            case Token_E::StringLiteral:
            case Token_E::CharLiteral: {
                    this->SetTokenType(this->current);
                    quote = this->current;
                    this->current = this->m_window.PushBack<u8>();

                parse_quote:
                    switch (this->current) {
                        // Newline
                        case '\n': {
                                this->IncrementRow();
                                // Temp fix for newlines in strings
                                // as this fixes the column calculation
                                this->lastRowIndex -= 2;
                                break;
                            }

                        // Backslash
                        case '\\': {
                                if (this->m_window.Back(1) == quote)
                                    this->m_window.IncTail();
                                break;
                            }

                        // Closing quote
                        default:
                            if (this->current == quote)
                                goto increment_and_return;
                    };

                    this->current = this->m_window.PushBack<u8>();

                    if (this->m_subTokens.IsSubViewInBounds(m_window))
                        goto parse_quote;

                    // TODO: Throw compiler error if incomplete
                    this->incomplete = true;
                    goto return_token;
                };
            // Numeric Literals -----------------------
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
                            if (this->m_window.Back<u8>() == '.' && this->m_subTokens.IsSubViewInBounds(m_window))
                                goto number;
                            goto increment_and_return;
                    };
                }

            // Identifiers -----------------------
            case Token_E::Upper_A:
            case Token_E::Upper_B:
            case Token_E::Upper_C:
            case Token_E::Upper_D:
            case Token_E::Upper_E:
            case Token_E::Upper_F:
            case Token_E::Upper_G:
            case Token_E::Upper_H:
            case Token_E::Upper_I:
            case Token_E::Upper_J:
            case Token_E::Upper_K:
            case Token_E::Upper_L:
            case Token_E::Upper_M:
            case Token_E::Upper_N:
            case Token_E::Upper_O:
            case Token_E::Upper_P:
            case Token_E::Upper_Q:
            case Token_E::Upper_R:
            case Token_E::Upper_S:
            case Token_E::Upper_T:
            case Token_E::Upper_U:
            case Token_E::Upper_V:
            case Token_E::Upper_W:
            case Token_E::Upper_X:
            case Token_E::Upper_Y:
            case Token_E::Upper_Z:
            case Token_E::Lower_A:
            case Token_E::Lower_B:
            case Token_E::Lower_C:
            case Token_E::Lower_D:
            case Token_E::Lower_E:
            case Token_E::Lower_F:
            case Token_E::Lower_G:
            case Token_E::Lower_H:
            case Token_E::Lower_I:
            case Token_E::Lower_J:
            case Token_E::Lower_K:
            case Token_E::Lower_L:
            case Token_E::Lower_M:
            case Token_E::Lower_N:
            case Token_E::Lower_O:
            case Token_E::Lower_P:
            case Token_E::Lower_Q:
            case Token_E::Lower_R:
            case Token_E::Lower_S:
            case Token_E::Lower_T:
            case Token_E::Lower_U:
            case Token_E::Lower_V:
            case Token_E::Lower_W:
            case Token_E::Lower_X:
            case Token_E::Lower_Y:
            case Token_E::Lower_Z:
            case Token_E::Underscore: {
                    this->current = this->m_window.PushBack<u8>();
                    this->SetTokenType(Token_E::Identifier);
                identifier:
                    switch (static_cast<Token_E>(this->current)) {
                        case Token_E::Upper_A:
                        case Token_E::Upper_B:
                        case Token_E::Upper_C:
                        case Token_E::Upper_D:
                        case Token_E::Upper_E:
                        case Token_E::Upper_F:
                        case Token_E::Upper_G:
                        case Token_E::Upper_H:
                        case Token_E::Upper_I:
                        case Token_E::Upper_J:
                        case Token_E::Upper_K:
                        case Token_E::Upper_L:
                        case Token_E::Upper_M:
                        case Token_E::Upper_N:
                        case Token_E::Upper_O:
                        case Token_E::Upper_P:
                        case Token_E::Upper_Q:
                        case Token_E::Upper_R:
                        case Token_E::Upper_S:
                        case Token_E::Upper_T:
                        case Token_E::Upper_U:
                        case Token_E::Upper_V:
                        case Token_E::Upper_W:
                        case Token_E::Upper_X:
                        case Token_E::Upper_Y:
                        case Token_E::Upper_Z:
                        case Token_E::Lower_A:
                        case Token_E::Lower_B:
                        case Token_E::Lower_C:
                        case Token_E::Lower_D:
                        case Token_E::Lower_E:
                        case Token_E::Lower_F:
                        case Token_E::Lower_G:
                        case Token_E::Lower_H:
                        case Token_E::Lower_I:
                        case Token_E::Lower_J:
                        case Token_E::Lower_K:
                        case Token_E::Lower_L:
                        case Token_E::Lower_M:
                        case Token_E::Lower_N:
                        case Token_E::Lower_O:
                        case Token_E::Lower_P:
                        case Token_E::Lower_Q:
                        case Token_E::Lower_R:
                        case Token_E::Lower_S:
                        case Token_E::Lower_T:
                        case Token_E::Lower_U:
                        case Token_E::Lower_V:
                        case Token_E::Lower_W:
                        case Token_E::Lower_X:
                        case Token_E::Lower_Y:
                        case Token_E::Lower_Z:
                        case Token_E::Underscore:
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
                                this->current = this->m_window.PushBack<u8>();
                                if (this->m_subTokens.IsSubViewInBounds(m_window)) {
                                    goto identifier;
                                }
                                goto return_token;
                            }

                    }
                    goto increment_and_return;
                }

            // Invalid Tokens -----------------------
            default:
                this->SetTokenType(Token_E::Invalid);
                goto increment_and_return;
        }



        this->m_window.IncTail();

        if (this->m_subTokens.IsSubViewInBounds(m_window))
            goto next_sub_token;


    increment_and_return_set_current:
        this->SetTokenType(current);

    increment_and_return:
        this->m_window.IncTail();

    return_token:
        Token token(this->m_window, reinterpret_cast<u64>(this->m_window.GetHead() - this->lastRowIndex), this->row, this->currentType);
        this->m_window.SetHeadToTail();
        this->SetTokenType(Token_E::Invalid);
        return token;
    }
}
