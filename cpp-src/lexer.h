#pragma once

#include <string>
#include <vector>

// TODO: This doesn't work at all
enum TokenType {
    // Objects
    Number, // 1, 20, 1.2
    Literal, // First Name
    String, // "Kate"

    // Symbols
    LParan,
    RParan,

    // Operations
    Selection, // σ, sigma
    /*Projection, // π, pi
    Product, // Χ, chi
    Join, // ⋈, theta
    Rename, // ρ, rho

    // Set
    Union, // ∪
    Intersect, // ∩

    // Comparison
    GreaterThan,
    LessThan,
    GreaterEq,
    LessEq,*/
    Equal,
    //NotEqual,
};

// Stream
struct Stream {
    const std::string &input;
    size_t index = 0;
    char peek() const;
    char eat();
};

// We store the stream location, data, and tt for each token
struct Token {
    size_t start;
    size_t end;
    std::string data;
    TokenType tt;

    Token(const Stream &s, char next, TokenType tt);
    Token(const Stream &s, TokenType tt);
    void finish(const Stream &s);
    void print() const;
};

std::vector<Token> lex(const std::string &input);
