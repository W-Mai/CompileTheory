//
// Created by W-Mai on 2021/5/6.
//

#include "Parser.h"

string S(Lexer *lexer);

string E(Lexer *lexer);

string E_(Lexer *lexer);

string T(Lexer *lexer);

string T_(Lexer *lexer);

string F(Lexer *lexer);

string make_temporary_var();

string make_tri(string &lv, string &rv);

Parser::Parser(Lexer *lex) {
    lexer = lex;
}

void Parser::parse() {
    lexer->next();
    S(lexer);
}

string S(Lexer *lexer) {
    auto f = F(lexer);
    auto token = lexer->current();
    if (token.syn == TOKEN_SYN::SYM_EQUAL){
        lexer->next();
        auto tmp = E(lexer);

        make_tri(f, tmp);
    }
    return {};
}

string E(Lexer *lexer) {
    auto tmp = T(lexer);
    tmp += E_(lexer);
    auto tVar = make_temporary_var();
    make_tri(tVar, tmp);
    return tVar;
}

string E_(Lexer *lexer) {
    auto token = lexer->current();
    switch (token.syn) {
        case TOKEN_SYN::SYM_PLUS: {
            lexer->next();
            string tmp = T(lexer);
            tmp += E_(lexer);

            auto tVar = make_temporary_var();
            make_tri(tVar, tmp);

            return " + " + tVar;
        }
        case TOKEN_SYN::SYM_MINUS: {
            lexer->next();
            string tmp = T(lexer);
            tmp += E_(lexer);

            auto tVar = make_temporary_var();
            make_tri(tVar, tmp);

            return " - " + tVar;
        }
        case TOKEN_SYN::EOF_:
//            cout << "Access" << endl;
//            exit(0);
        default:
            break;
    }
    return {};
}

string T(Lexer *lexer) {
    auto tmp = F(lexer);
    tmp += T_(lexer);

    auto tVar = make_temporary_var();
    make_tri(tVar, tmp);
    return tVar;
}

string T_(Lexer *lexer) {
    auto token = lexer->current();
    switch (token.syn) {
        case TOKEN_SYN::SYM_ASTERISK: {
            lexer->next();
            string tmp = F(lexer);
            tmp = tmp + T_(lexer);

            auto tVar = make_temporary_var();
            make_tri(tVar, tmp);

            return " * " + tVar;
        }
        case TOKEN_SYN::SYM_SLASH: {
            lexer->next();
            string tmp = F(lexer);
            tmp = tmp + T_(lexer);

            auto tVar = make_temporary_var();
            make_tri(tVar, tmp);

            return " / " + tVar;
        }
        case TOKEN_SYN::EOF_:
//            cout << "Access" << endl;
        default:
            break;
    }
    return {};
}

string F(Lexer *lexer) {
    auto token = lexer->current();
    switch (token.syn) {
        case TOKEN_SYN::ID:
            lexer->next();
            return (char *) (token.token);
        case TOKEN_SYN::NUM:
            lexer->next();
            return (char *) (token.token);
        case TOKEN_SYN::SYM_PARENTHESES_LEFT: {
            lexer->next();
            string tmp = /*"(" + */E(lexer);
            if (lexer->current().syn != TOKEN_SYN::SYM_PARENTHESES_RIGHT) break;
            lexer->next();
            return tmp/* + ")"*/;
        }
        case TOKEN_SYN::EOF_:
//            cout << "Access" << endl;
//            exit(0);
        default:
            break;
    }
    return {};
}

int count = 0;

string make_temporary_var() {
    return "T" + to_string(count++);
}

string make_tri(string &lv, string &rv) {
    cout << lv << " = " << rv << endl;
    return {};
}