//
// Created by W-Mai on 2021/4/28.
//

#include <cstring>
#include "Lexer.h"

const char *KEY_WORD[] = {"main", "int", "char", "if", "else", "for", "while"};

Lexer::Lexer(uint8_t *src) {
    code_ptr = src;
    current_index = 0;
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
                tmp_token = Token{TOKEN_SYN::SYN_LOGICAL_EQUAL, (uint8_t *) "=="};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYM_EQUAL, (uint8_t *) "="};
            break;
        case '+':
            tmp_token = Token{TOKEN_SYN::SYM_PLUS, (uint8_t *) "+"};
            nc();
            break;
        case '-':
            tmp_token = Token{TOKEN_SYN::SYM_MINUS, (uint8_t *) "-"};
            nc();
            break;
        case '*':
            tmp_token = Token{TOKEN_SYN::SYM_ASTERISK, (uint8_t *) "*"};
            nc();
            break;
        case '/':
            tmp_token = Token{TOKEN_SYN::SYM_SLASH, (uint8_t *) "/"};
            nc();
            break;
        case '(':
            tmp_token = Token{TOKEN_SYN::SYM_PARENTHESES_LEFT, (uint8_t *) "("};
            nc();
            break;
        case ')':
            tmp_token = Token{TOKEN_SYN::SYM_PARENTHESES_RIGHT, (uint8_t *) ")"};
            nc();
            break;
        case '[':
            tmp_token = Token{TOKEN_SYN::SYM_BRACKETS_LEFT, (uint8_t *) "["};
            nc();
            break;
        case ']':
            tmp_token = Token{TOKEN_SYN::SYM_BRACKETS_RIGHT, (uint8_t *) "]"};
            nc();
            break;
        case '{':
            tmp_token = Token{TOKEN_SYN::SYM_BRACE_LEFT, (uint8_t *) "{"};
            nc();
            break;
        case '}':
            tmp_token = Token{TOKEN_SYN::SYM_BRACE_RIGHT, (uint8_t *) "}"};
            nc();
            break;
        case ',':
            tmp_token = Token{TOKEN_SYN::SYM_COMMA, (uint8_t *) ","};
            nc();
            break;
        case ':':
            tmp_token = Token{TOKEN_SYN::SYM_COLON, (uint8_t *) ":"};
            nc();
            break;
        case ';':
            tmp_token = Token{TOKEN_SYN::SYM_SEMICOLON, (uint8_t *) ";"};
            nc();
            break;
        case '>':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_GREATER_EQUAL, (uint8_t *) ">="};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYN_GREATER, (uint8_t *) ">"};
            break;
        case '<':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_LESSER_EQUAL, (uint8_t *) "<="};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYN_LESSER, (uint8_t *) "<"};
            break;
        case '!':
            nc();
            if (gc() == '=') {
                tmp_token = Token{TOKEN_SYN::SYN_NOT_EQUAL, (uint8_t *) "!="};
                nc();
                break;
            }
            tmp_token = Token{TOKEN_SYN::SYN_NOT, (uint8_t *) "!"};
            break;
        case 0:
            tmp_token = Token{TOKEN_SYN::EOF_, (uint8_t *) "\0"};
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
                tmp_str_index_end = current_index + 1;
            }
            tmp_str_len = tmp_str_index_end - current_index;
            tmp_token = make_token(tmp_syn, tmp_str_len);
            copy_str(tmp_token.token, tmp_str_index_end);
            if (tmp_token.syn == TOKEN_SYN::ID) {
                TOKEN_SYN tmp_keyword_syn = is_key_word(reinterpret_cast<const char *>(tmp_token.token));
                if (tmp_keyword_syn != TOKEN_SYN::ERROR) {
                    tmp_token.syn = tmp_keyword_syn;
                }
            }
    }

    return tmp_token;
}

uint8_t Lexer::gc() const {
    return code_ptr[current_index];
}

uint8_t Lexer::nc() {
    return code_ptr[current_index++];
}

bool Lexer::is_digit(uint8_t ch) {
    return '0' <= ch and ch <= '9';
}

bool Lexer::is_letter(uint8_t ch) {
    return ('a' <= ch and ch <= 'z') or ('A' <= ch and ch <= 'Z');
}

int32_t Lexer::read_num() const {
    int32_t t = current_index;
    while (is_digit(code_ptr[t]))t++;
    return t;
}

int32_t Lexer::read_id() const {
    int32_t t = current_index + 1; //第一个肯定是字母，所以跳过第一个，符合文法规定。
    while (is_letter(code_ptr[t]) or is_digit(code_ptr[t]))t++;
    return t;
}

void Lexer::eat_whitespace() {
    while (is_whitespace(gc()))nc();
}

bool Lexer::is_whitespace(uint8_t ch) {
    return ch == ' ' or ch == '\t' or ch == '\r' or ch == '\n';
}

void Lexer::copy_str(uint8_t *dst, int32_t dst_index) {
    if (!dst)return;
    for (int i = current_index; i < dst_index; ++i) {
        dst[i - current_index] = code_ptr[i];
    }
    current_index = dst_index;
}

Token Lexer::make_token(TOKEN_SYN syn, uint32_t length) {
    auto *token = new Token;
    token->syn = syn;
    token->token = new uint8_t[length + 1];
    token->token[length] = 0;
    return *token;
}

TOKEN_SYN Lexer::is_key_word(const char *word) {
    int arr_len = (sizeof KEY_WORD) / (sizeof *KEY_WORD);
    for (int i = 0; i < arr_len; ++i) {
        if (!strcmp(word, KEY_WORD[i]))return static_cast<TOKEN_SYN>(i + 1);
    }
    return TOKEN_SYN::ERROR;
}
