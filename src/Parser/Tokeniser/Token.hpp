#pragma once
#include "../../Types/SlideView.hpp"

namespace Match::Parser
{
    class Token
    {
    public:
        Token(SlideViewChar subTokens, uSize column, uSize row) : m_subTokens(subTokens), m_column(column), m_row(row) {}
        Token() {}
        ~Token() {}

        SlideViewChar GetSubTokens() const { return m_subTokens; }
        std::string_view GetSubTokensAsStr() const { return m_subTokens; }
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
    };
}