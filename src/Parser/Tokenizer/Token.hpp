#pragma once
#include "../../Types/SlideView.hpp"

namespace Match::Parser {

    enum Token_E {
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
            Number,
    };

    class Token {
    public:
        Token(SlideView<u8> subTokens, u64 column, u64 row, Token_E type) : m_subTokens(subTokens), m_column(column), m_row(row), m_type(type) {}
        Token() {}
        ~Token() {}

        SlideView<u8> GetSubTokens() const { return m_subTokens; }

        //std::string_view GetSubTokensAsStr() { return m_subTokens.ToString<char>(); }

        u64 GetColumn() const { return m_column; }
        u64 GetRow() const { return m_row; }
        u64 Length() const { return m_subTokens.Size(); }

        void SetSubTokens(SlideView<u8> subTokens) { m_subTokens = subTokens; }
        void SetColumn(u64 column) { m_column = column; }
        void SetRow(u64 row) { m_row = row; }

        inline std::string ToString() {
            switch (m_type) {
            case Token_E::Whitespace:
                return "Whitespace";
            case Token_E::Comment:
                return "Comment";
            case Token_E::Identifier:
                return "Identifier";
            case Token_E::Keyword:
                return "Keyword";
            case Token_E::Operator:
                return "Operator";
            case Token_E::Literal:
                return "Literal";
            case Token_E::Unknown:
                return "Unknown";
            case Token_E::CharLiteral:
                return "CharLiteral";
            case Token_E::StringLiteral:
                return "StringLiteral";
            case Token_E::Delimiter:
                return "Delimiter";
            case Token_E::ListSeparator:
                return "ListSeparator";
            case Token_E::TypeSeparator:
                return "TypeSeparator";
            case Token_E::InstanceAccess:
                return "InstanceAccess";
            case Token_E::ScopeResolution:
                return "ScopeResolution";
            default:
                return "Unknown";
            }
            return "Unknown";
        }

    private:
        SlideView<u8> m_subTokens = {};
        u64 m_column = 0;
        u64 m_row = 0;
        Token_E m_type = Token_E::Unknown;
    };
}