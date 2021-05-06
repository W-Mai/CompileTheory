//
// Created by W-Mai on 2021/5/6.
//

#ifndef COMPILETHEORY_PARSER_H
#define COMPILETHEORY_PARSER_H

#include <cinttypes>
#include "Lexer.h"

struct NodeVal {
    Token val;
};

struct NodeExpression {
    NodeExpression *left;
    NodeExpression *op;
    NodeExpression *right;
};

struct NodeBinaryExpression : NodeExpression {

};

struct NodeFunction {
    Token name;
};

union ASTNodeVal {
    NodeVal val;
    NodeExpression expression;
    NodeFunction function;
};


struct Program {

};

class Parser {
public:
    explicit Parser(Lexer *lexer);
};


#endif //COMPILETHEORY_PARSER_H
