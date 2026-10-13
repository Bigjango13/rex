#pragma once

#include <unordered_map>

#include "parser.h"
#include "db.h"

struct EngineError {
    std::string msg;
};

class Engine {
public:
    std::unordered_map<std::string, Table*> tables = {};
    Table *anon = nullptr;
    void free_anon() {
        if (anon && anon->name == "") {
            delete(anon);
            anon = nullptr;
        }
    }
    // Used for row by row evals
    int tb_index = 0;

    std::vector<EngineError> errors = {};
    bool error(const std::string &msg);

    bool eval_binop_expr(Table *target, Record &val, BinopNode *node);
    bool eval_expr(Table *target, Record &val, ASTNode *node);

    bool run_select(SelectTableNode *node);
    bool run_lit(BaseLitExprNode *node);
    bool run_node(ASTNode *node, bool tl = false);

    void print();

    Engine() {}
};
