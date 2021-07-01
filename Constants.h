//
// Created by Esther on 2021/7/1.
//

#ifndef COMPILETHEORY_CONSTANTS_H
#define COMPILETHEORY_CONSTANTS_H

#include <iostream>
#include <stack>
#include <map>
#include <vector>

extern const std::string KEY_WORD[];

enum TOKEN_SYN {
    MAIN = 1,
    INT = 2,
    FLOAT = 3,
    IF = 4,
    ELSE = 5,
    FOR = 6,
    WHILE = 7,
    CONTINUE = 8,
    BREAK = 9,
    MATRIX = 10,

    ID = 15,
    NUM = 20,

    SYM_EQUAL = 30,
    SYM_PLUS = 31,
    SYM_MINUS = 32,
    SYM_ASTERISK = 33,
    SYM_SLASH = 34,
    SYM_PARENTHESES_LEFT = 35,
    SYM_PARENTHESES_RIGHT = 36,
    SYM_BRACKETS_LEFT = 37,
    SYM_BRACKETS_RIGHT = 38,
    SYM_BRACE_LEFT = 39,
    SYM_BRACE_RIGHT = 40,
    SYM_COMMA = 41,
    SYM_COLON = 42,
    SYM_SEMICOLON = 43,
    SYN_GREATER = 44,
    SYN_LESSER = 45,
    SYN_GREATER_EQUAL = 46,
    SYN_LESSER_EQUAL = 47,
    SYN_LOGICAL_EQUAL = 48,
    SYN_NOT = 49,
    SYN_NOT_EQUAL = 50,
    SYN_VERTICAL_LINE = 51,
    EOF_ = 1000,
    ERROR = -1
};

struct TokenPos {
    int32_t row, col, index;
};

struct Token {
    TOKEN_SYN syn;
    std::string token;
    TokenPos start_pos;
    TokenPos end_pos;

    void print() const {
        std::cout << "(" << syn << "," << token << ") {"
                  << start_pos.row << ", " << start_pos.col << ", " << start_pos.index << "} - {"
                  << end_pos.row << ", " << end_pos.col << ", " << end_pos.index << "}";
    }
};

struct QuadExpression {
    std::string op;
    std::string left;
    std::string right;
    std::string res;
};

struct Program {

};

typedef std::stack<Token> DealStack;

enum TableElementType {
    NOTHING,
    STATUS,
    GENERATE_EXPR
};

struct TableElement {
    TableElementType type = TableElementType::NOTHING;
    int id{};
};

struct GenExpr {
    std::string left;
    std::vector<Token> right;
};

typedef std::map<TOKEN_SYN, std::vector<TableElement>> ACTIONTable_type;
typedef std::map<std::string, std::vector<TableElement>> GOTOTable_type;

#endif //COMPILETHEORY_CONSTANTS_H
