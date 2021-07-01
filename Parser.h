//
// Created by W-Mai on 2021/5/6.
//

#ifndef COMPILETHEORY_PARSER_H
#define COMPILETHEORY_PARSER_H

#include <cinttypes>
#include <stack>
#include <vector>
#include "Lexer.h"
#include "LRTables.h"



class Parser {
private:
    DealStack Symbols;
    DealStack Status;

    Lexer *lexer;
public:
    explicit Parser(Lexer *lexer);
};


#endif //COMPILETHEORY_PARSER_H
