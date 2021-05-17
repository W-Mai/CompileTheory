//
// Created by W-Mai on 2021/5/6.
//

#include "Parser.h"

void E(Lexer *lexer);

void E_(Lexer *lexer);

void T(Lexer *lexer);

void T_(Lexer *lexer);

void F(Lexer *lexer);

void F_(Lexer *lexer);


Parser::Parser(Lexer *lex) {
    lexer = lex;
}

void Parser::parse() {
    lexer->next();
    E(lexer);
}

void E(Lexer *lexer) {
    T(lexer);
    E_(lexer);
}

void E_(Lexer *lexer) {
    auto token = lexer->current();
//    token.print();
    switch (token.syn) {
        case TOKEN_SYN::SYM_PLUS:
            lexer->next();
            T(lexer);
            E_(lexer);
            break;
        case TOKEN_SYN::SYM_MINUS:
            lexer->next();
            T(lexer);
            E_(lexer);
            break;
        case TOKEN_SYN::EOF_:
            cout << "Access" << endl;
            exit(0);
        default:
            break;
    }
}

void T(Lexer *lexer) {
    F(lexer);
    T_(lexer);
}

void T_(Lexer *lexer) {
    auto token = lexer->current();
//    token.print();
    switch (token.syn) {
        case TOKEN_SYN::SYM_ASTERISK:
            lexer->next();
            F(lexer);
            T_(lexer);
            break;
        case TOKEN_SYN::SYM_SLASH:
            lexer->next();
            F(lexer);
            T_(lexer);
            break;
        case TOKEN_SYN::EOF_:
            cout << "Access" << endl;
            exit(0);
        default:
            break;
    }
}

void F(Lexer *lexer) {
    auto token = lexer->current();
//    token.print();
    switch (token.syn) {
        case TOKEN_SYN::ID:
            lexer->next();
            break;
        case TOKEN_SYN::NUM:
            lexer->next();
            break;
        case TOKEN_SYN::SYM_PARENTHESES_LEFT:
            lexer->next();
            E(lexer);
            if (lexer->current().syn != TOKEN_SYN::SYM_PARENTHESES_RIGHT) break;
            lexer->next();
            break;
        case TOKEN_SYN::EOF_:
            cout << "Access" << endl;
            exit(0);
        default:
            break;
    }
}
