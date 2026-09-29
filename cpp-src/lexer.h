#pragma once

#include <string>
#include <vector>

// TODO: This doesn't work at all
enum TokenType {
    // Objects
    Number = 0, // 1, 20, 1.2
    Literal = 1, // First Name
    String = 2, // "Kate"

    // Symbols
    LParan = 3,
    RParan = 4,
    Equal = 5,

    // Operations
    Selection = 6, // σ, sigma
    /*Projection, // π, pi
    Product, // Χ, chi
    Join, // ⋈, theta
    Rename, // ρ, rho

    // Set
    Union = x, // ∪
    Intersect = x, // ∩

    // Comparison
    GreaterThan = x,
    LessThan = x,
    GreaterEq = x,
    LessEq = x,*/
    //NotEqual = x,
};

// Stream
struct Stream {
    const std::string &input;
    size_t index = 0;
    std::string peek() const;
    std::string eat();
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
