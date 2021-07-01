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

    string code_ptr;
    TokenPos current_index{};
    int32_t current_index_end;

    inline uint8_t gc() const; // get char;
    inline uint8_t nc(); // next char;
    static inline bool is_digit(uint8_t ch);

    static inline bool is_letter(uint8_t ch);

    static inline bool is_whitespace(uint8_t ch);

    static TOKEN_SYN is_key_word(const string &word);

    void copy_str(string &dst, int32_t dst_index);

    int32_t read_num();

    int32_t read_id();

    void eat_whitespace();


public:

    explicit Lexer(string &src);

    Token next();

    Token make_token(TOKEN_SYN syn);
};


#endif //COMPILETHEORY_LEXER_H
