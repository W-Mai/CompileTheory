//
// Created by W-Mai on 2021/4/28.
//

#ifndef COMPILETHEORY_LEXER_H
#define COMPILETHEORY_LEXER_H

#include <iostream>
#include "cinttypes"

using namespace std;

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
    uint8_t *token;
    TokenPos start_pos;
    TokenPos end_pos;

    void print() const {
        std::cout << "(" << syn << "," << token << ") {"
                  << start_pos.row << ", " << start_pos.col << ", " << start_pos.index << "} - {"
                  << end_pos.row << ", " << end_pos.col << ", " << end_pos.index << "}";
    }
};

class Lexer {

    uint8_t *code_ptr;
    TokenPos current_index{};
    int32_t current_index_end;

    inline uint8_t gc() const; // get char;
    inline uint8_t nc(); // next char;
    static inline bool is_digit(uint8_t ch);

    static inline bool is_letter(uint8_t ch);

    static inline bool is_whitespace(uint8_t ch);

    static TOKEN_SYN is_key_word(const char *word);

    void copy_str(uint8_t *dst, int32_t dst_index);

    int32_t read_num();

    int32_t read_id();

    void eat_whitespace();


public:

    explicit Lexer(uint8_t *src);

    Token next();

    Token make_token(TOKEN_SYN syn, uint32_t length);
};


#endif //COMPILETHEORY_LEXER_H
