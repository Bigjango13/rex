#include <cmath>

#include "parser.h"

#define ERR(x) if (x.get() == nullptr) return x

static double string_to_double(const std::string &str) {
    char *end = NULL;
    double val = strtod(str.c_str(), &end);
    if (end != str.c_str() && *end == '\0') {
        return HUGE_VAL;
    }
    return val;
}

Node Parser::parse_base_expr(Tokens tokens) {
    const Token &at = this->peek(tokens);
    if (at.tt == TokenType::LParan) {
        this->eat(tokens);
        Node ret = this->parse_tl_expr(tokens);
        if (this->peek(tokens).tt == TokenType::LParan) {
            this->eat(tokens);
        } else {
            // TODO: Error Messages
            return nullptr;
        }
        // Return
        return ret;
    } else if (at.tt == TokenType::Number) {
        // Eat, convert, and ret
        this->eat(tokens);
        double dval = string_to_double(at.data);
        // TODO: Error Messages
        if (dval == HUGE_VAL) return nullptr;
        return NODE<BaseNumExprNode>(dval);
    } else if (at.tt == TokenType::Literal) {
        // Eat and ret
        this->eat(tokens);
        return NODE<BaseLitExprNode>(at.data);
    } else if (at.tt == TokenType::String) {
        // Eat and ret
        this->eat(tokens);
        return NODE<BaseStrExprNode>(at.data);
    }
    // TODO: Error Messages
    return nullptr;
}

Node Parser::parse_binop_expr(Tokens tokens) {
    Node lhs = this->parse_base_expr(tokens);
    ERR(lhs);
    const Token &at = this->peek(tokens);
    // Binop
    if (at.tt == TokenType::Equal /*|| ...*/) {
        this->eat(tokens);
        Node rhs = this->parse_base_expr(tokens);
        ERR(rhs);
        // TODO: Beyond `TokenType::Equal`
        return NODE<BinopNode>(MOVE(lhs), MOVE(rhs), BinopType::Equals);
    }
    // Not a binop!
    return lhs;
}

Node Parser::parse_tl_expr(Tokens tokens) {
    return this->parse_binop_expr(tokens);
}

Node Parser::parse_table_expr(Tokens tokens) {
    const Token &at = this->peek(tokens);
    if (at.tt == TokenType::Selection) {
        // Parse selection
        this->eat(tokens);
        // Expression
        Node expr = this->parse_tl_expr(tokens);
        ERR(expr);
        // Table
        Node table = this->parse_table_expr(tokens);
        ERR(table);
        // Selection
        return NODE<SelectTableNode>(MOVE(table), MOVE(expr));
    } else if (at.tt == TokenType::Literal) {
        return NODE<BaseLitExprNode>(this->eat(tokens).data);
    }
    return nullptr;
}

Node Parser::parse(Tokens tokens) {
    // Top level parse
    return this->parse_table_expr(tokens);
}
