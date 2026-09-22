// (ab)using http://infolab.stanford.edu/~ullman/fcdb/aut07/slides/ra.pdf
#include <iostream>

#include "lexer.h"

// Stream
char Stream::peek() const {
    if (index >= input.size()) return '\0';
    return input[index];
}

char Stream::eat() {
    if (index >= input.size()) return '\0';
    return input[index++];
}

// Char tests
inline constexpr bool isalpha(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}
inline constexpr bool isnum(char c) {
    return '0' <= c && c <= '9';
}
inline constexpr bool isalphanum(char c) {
    return isalpha(c) || isnum(c);
}
inline constexpr bool islitchar(char c) {
    return isalpha(c) || isnum(c) || c == ' ';
}

// Token
Token::Token(const Stream &s, char next, TokenType tokt)
    : start(s.index), end(0), data(1, next), tt(tokt)
{}
Token::Token(const Stream &s, TokenType tokt)
    : start(s.index), end(0), data(""), tt(tokt)
{}

void Token::finish(const Stream &s) {
    end = s.index;
}

void Token::print() const {
    std::cout << "Tok{tt: " << tt << ", data: \"" << data << "\"}";
}


// Lexing
std::vector<Token> lex(const std::string &input) {
    Stream stream{input};
    std::vector<Token> ret{};

    char next = stream.peek();
    if (isalpha(next)) {
        // Literal/keyword
        Token nexttok(stream, TokenType::Literal);
        do {
            nexttok.data += stream.eat();
            next = stream.peek();
        } while (islitchar(next));
        nexttok.finish(stream);

        // Check if it's a keyword
        if (nexttok.data == "select") nexttok.tt = TokenType::Selection;
        ret.push_back(nexttok);
    } else if (next == '"') {
        // Strings
    }
    return ret;
}
