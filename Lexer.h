//
// Created by W-Mai on 2021/4/28.
//

#ifndef COMPILETHEORY_LEXER_H
#define COMPILETHEORY_LEXER_H

#include <iostream>
#include "cinttypes"
#include "Constants.h"

using namespace std;

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
