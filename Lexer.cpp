//
// Created by W-Mai on 2021/4/28.
//

#include <cstring>
#include "Lexer.h"

const string KEY_WORD[] = {"main", "int", "float", "if", "else", "for", "while", "continue", "break", "mat"};

Lexer::Lexer(string &src) {
    code_ptr = src;
    current_index = {0, 0, 0};
    current_index_end = 0;
}

Token Lexer::next() {
    int32_t tmp_str_index_end = 0;
    int32_t tmp_str_len = 0;
    TOKEN_SYN tmp_syn = TOKEN_SYN::ERROR;
    Token tmp_token{};

    eat_whitespace();

    uint8_t ch = gc();

    switch (ch) {
        case '=':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_LOGICAL_EQUAL, "==",
                                  {current_index.row, current_index.col - 1, current_index.index - 1}, current_index};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYM_EQUAL, "=",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            break;
        case '+':
            tmp_token = Token{TOKEN_SYN::SYM_PLUS, "+",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '-':
            tmp_token = Token{TOKEN_SYN::SYM_MINUS, "-",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '*':
            tmp_token = Token{TOKEN_SYN::SYM_ASTERISK, "*",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '/':
            tmp_token = Token{TOKEN_SYN::SYM_SLASH, "/",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '(':
            tmp_token = Token{TOKEN_SYN::SYM_PARENTHESES_LEFT, "(",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case ')':
            tmp_token = Token{TOKEN_SYN::SYM_PARENTHESES_RIGHT, ")",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '[':
            tmp_token = Token{TOKEN_SYN::SYM_BRACKETS_LEFT, "[",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case ']':
            tmp_token = Token{TOKEN_SYN::SYM_BRACKETS_RIGHT, "]",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '{':
            tmp_token = Token{TOKEN_SYN::SYM_BRACE_LEFT, "{",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '}':
            tmp_token = Token{TOKEN_SYN::SYM_BRACE_RIGHT, "}",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case ',':
            tmp_token = Token{TOKEN_SYN::SYM_COMMA, ",",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case ':':
            tmp_token = Token{TOKEN_SYN::SYM_COLON, ":",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case ';':
            tmp_token = Token{TOKEN_SYN::SYM_SEMICOLON, ";",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case '>':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_GREATER_EQUAL, ">=",
                                  {current_index.row, current_index.col - 1, current_index.index - 1}, current_index};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYN_GREATER, ">",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            break;
        case '<':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_LESSER_EQUAL, "<=",
                                  {current_index.row, current_index.col - 1, current_index.index - 1}, current_index};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYN_LESSER, "<",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            break;
        case '!':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_NOT_EQUAL, "!=",
                                  {current_index.row, current_index.col - 1, current_index.index - 1}, current_index};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYN_NOT, "!",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            break;
        case '|':
            tmp_token = Token{TOKEN_SYN::SYN_VERTICAL_LINE, "|",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        case 0:
            tmp_token = Token{TOKEN_SYN::EOF_, "",
                              {current_index.row, current_index.col, current_index.index}, current_index};
            nc();
            break;
        default:
            if (is_digit(ch)) {
                tmp_str_index_end = read_num();
                tmp_syn = TOKEN_SYN::NUM;
            } else if (is_letter(ch)) {
                tmp_str_index_end = read_id();
                tmp_syn = TOKEN_SYN::ID;
            } else {
                tmp_str_index_end = current_index.index + 1;
            }
            tmp_str_len = tmp_str_index_end - current_index.index;
            tmp_token = make_token(tmp_syn);
            copy_str(tmp_token.token, tmp_str_index_end);
            tmp_token.start_pos = {current_index.row, current_index.col - tmp_str_len,
                                   current_index.index - tmp_str_len - 1};
            tmp_token.end_pos = {current_index.row, tmp_token.start_pos.col + tmp_str_len - 1,
                                 tmp_token.start_pos.index + tmp_str_len - 1};
            if (tmp_token.syn == TOKEN_SYN::ID) {
                TOKEN_SYN tmp_keyword_syn = is_key_word((tmp_token.token));
                if (tmp_keyword_syn != TOKEN_SYN::ERROR) {
                    tmp_token.syn = tmp_keyword_syn;
                }
            }
    }

    return tmp_token;
}

uint8_t Lexer::gc() const {
    return code_ptr[current_index.index];
}

uint8_t Lexer::nc() {
    current_index.col++;
    if (gc() == '\r') {
        current_index.col = 0;
        current_index.row++;
        current_index.index++;
        if (gc() != '\n')return gc();
    }
    return code_ptr[current_index.index++];
}

bool Lexer::is_digit(uint8_t ch) {
    return '0' <= ch and ch <= '9';
}

bool Lexer::is_letter(uint8_t ch) {
    return ('a' <= ch and ch <= 'z') or ('A' <= ch and ch <= 'Z');
}

int32_t Lexer::read_num() {
    int32_t t = current_index.index;
    while (is_digit(code_ptr[t]))t++;
    current_index.col += t - current_index.index;
    return t;
}

int32_t Lexer::read_id() {
    int32_t t = current_index.index + 1; //第一个肯定是字母，所以跳过第一个，符合文法规定。
    while (is_letter(code_ptr[t]) or is_digit(code_ptr[t]))t++;
    current_index.col += t - current_index.index;
    return t;
}

void Lexer::eat_whitespace() {
    while (is_whitespace(gc()))nc();
}

bool Lexer::is_whitespace(uint8_t ch) {
    return ch == ' ' or ch == '\t' or ch == '\r' or ch == '\n';
}

void Lexer::copy_str(string &dst, int32_t dst_index) {
//    if (!dst.length())return;
    dst = string(code_ptr.begin() + current_index.index, code_ptr.begin() + dst_index);
    current_index.index = dst_index;
}

Token Lexer::make_token(TOKEN_SYN syn) {
    Token token;
    token.syn = syn;
    token.token = "";
    token.start_pos = current_index;
    return token;
}

TOKEN_SYN Lexer::is_key_word(const string &word) {
    int arr_len = (sizeof KEY_WORD) / (sizeof *KEY_WORD);
    for (int i = 0; i < arr_len; ++i) {
        if (word == KEY_WORD[i])return static_cast<TOKEN_SYN>(i + 1);
    }
    return TOKEN_SYN::ERROR;
}
