#pragma once

#include "Logs/Logs.hpp"
#include "Parser/Tokenizer/Tokenizer.hpp"
#include <iostream>
#include <string>
#include <print>
#include <optional>
#include <variant>
#include <span>
#include <algorithm>
#include <string_view>
#include <expected>
using namespace match::parser;
using namespace match;

#define const_str(class_name, const_name, str, len)           \
    const char const_name[] = str;                            \
    using class_name = ConstStrBase<const_name, len>; \



namespace str {

    template<const char* str, const size_t len>
    class ConstStrBase {
        public:
        static  std::string_view MakeView() {
            return std::string_view(str, len);
        }
    };

    template <typename T>
    concept ConstStr = requires(T t) {
        { t.MakeView() } -> std::same_as<std::string_view>;
    };

    const_str(Comma, COMMA, ",", 1)
    const_str(CurlyBracketOpen, CURLY_BRACKET_OPEN, "{", 1)
    const_str(CurlyBracketClose, CURLY_BRACKET_CLOSE, "}", 1)
    const_str(SquareBracketOpen, SQUARE_BRACKET_OPEN, "[", 1)
    const_str(SquareBracketClose, SQUARE_BRACKET_CLOSE, "]", 1)
    const_str(AngleBracketOpen, ANGLE_BRACKET_OPEN, "<", 1)
    const_str(AngleBracketClose, ANGLE_BRACKET_CLOSE, ">", 1)
    const_str(ScopeResolution, SCOPE_RESOLUTION, "::", 2)
    const_str(ParenthesisOpen, PARENTHESIS_OPEN, "(", 1)
    const_str(ParenthesisClose, PARENTHESIS_CLOSE, ")", 1)
}

enum class AstNodeTag : int {};

enum class AstError : int {

    Unimplemented,
    ExpectedToken,
    ExpectedAstNode
};

class AstBase {
    public:
    //AstNodeTag m_tag;

    AstBase() {};
    virtual ~AstBase() {}

    virtual std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) = 0;
};

template <class T>
concept AstParse = requires(T t, std::span<Token> tokens) {
    { t.parse(tokens) } -> std::same_as<std::expected<std::span<Token>,AstError>>;
};

template <AstParse T>
class AstNode : public AstBase {

    public:
    AstNode() {}
    ~AstNode() {}


    virtual std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override = 0;

    inline T GetChildren() const {
        return this->m_children;
    }

    protected:
    std::vector<T> m_children{};

};

template<AstParse T, str::ConstStr sep>
class AstSeparated : public AstNode<T> {
    public:
    AstSeparated() {}
    ~AstSeparated() {}

     std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override;
};

template<AstParse T>
using AstCommaSeparated = AstSeparated<T, str::Comma>;

template<AstParse T, str::ConstStr start, str::ConstStr end>

class AstDelimited : public AstNode<T> {
    public:
    AstDelimited() {}
    ~AstDelimited() {}

    std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override;
};


class AstVariable : public AstBase {
    public:
    AstVariable() {}
    ~AstVariable() {}

    std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override;
};

template<AstParse T>
using RoundCommaDelimited = AstDelimited<AstCommaSeparated<T>, str::ParenthesisOpen, str::ParenthesisClose>;

template<AstParse T>
using AngleCommaDelimited = AstDelimited<AstCommaSeparated<T>, str::AngleBracketOpen, str::AngleBracketClose>;

using AstParameter = RoundCommaDelimited<AstVariable>;


using TemplateArguments = AngleCommaDelimited<AstVariable>;



class AstLabel : public AstBase {
    public:
    AstLabel() {}
    ~AstLabel() {}

    std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override;
};

class AstType : public AstBase {
    public:
    AstType() {}
    ~AstType() {}

    std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override;
};

class AstFunctionHeader : public AstBase {
    public:
    AstFunctionHeader() {}
    ~AstFunctionHeader() {}

    //AstParameter parameters;
    std::string_view ident;
    AstType return_type;
    AstLabel visibility;
    // TODO: templates

    std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) override;
};


class Ast {
    // Implementation
};


//class AstClass : public AstNodeBase {
//	
//	
//	
//	
//};
//
//// The root
//class AstNamespace : public AstNodeBase {};





