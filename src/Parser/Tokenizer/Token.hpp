#pragma once
#include "../../Types/SlideView.hpp"

namespace Match::Parser
{

    enum TokenType
    {
        Whitespace,
        Comment,
        Identifier,
        Keyword,
        Operator,
        Literal,
        Unknown,
        CharLiteral,
        StringLiteral,
        Delimiter,
        ListSeparator,
        TypeSeparator,
        InstanceAccess,
        ScopeResolution,

    };
    class Token
    {
    public:
        Token(SlideViewChar subTokens, uSize column, uSize row, TokenType type) : m_subTokens(subTokens), m_column(column), m_row(row), m_type(type) {}
        Token() {}
        ~Token() {}

        SlideViewChar GetSubTokens() const { return m_subTokens; }
        std::string_view GetSubTokensAsStr() { return m_subTokens.ToString(); }
        uSize GetColumn() const { return m_column; }
        uSize GetRow() const { return m_row; }
        uSize Length() const { return m_subTokens.Size(); }

        void SetSubTokens(SlideViewChar subTokens) { m_subTokens = subTokens; }
        void SetColumn(uSize column) { m_column = column; }
        void SetRow(uSize row) { m_row = row; }

        inline std::string ToString()
        {
            switch (m_type)
            {
                case TokenType::Whitespace:
                return "Whitespace";
            case TokenType::Comment:
                return "Comment";
            case TokenType::Identifier:
                return "Identifier";
            case TokenType::Keyword:
                return "Keyword";
            case TokenType::Operator:
                return "Operator";
            case TokenType::Literal:
                return "Literal";
            case TokenType::Unknown:
                return "Unknown";
            case TokenType::CharLiteral:
                return "CharLiteral";
            case TokenType::StringLiteral:
                return "StringLiteral";
            case TokenType::Delimiter:
                return "Delimiter";
            case TokenType::ListSeparator:
                return "ListSeparator";
            case TokenType::TypeSeparator:
                return "TypeSeparator";
            case TokenType::InstanceAccess:
                return "InstanceAccess";
            case TokenType::ScopeResolution:
                return "ScopeResolution";
            default:
                return "Unknown";
            }
            return "Unknown";

        }
    private:
        SlideViewChar m_subTokens = {};
        uSize m_column = 0;
        uSize m_row = 0;
        TokenType m_type = TokenType::Unknown;
    };
}