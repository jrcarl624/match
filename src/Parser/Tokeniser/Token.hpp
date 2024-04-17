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
    private:
        SlideViewChar m_subTokens = {};
        uSize m_column = 0;
        uSize m_row = 0;
        TokenType m_type = TokenType::Unknown;
    };
}