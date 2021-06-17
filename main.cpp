#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

Lexer *lexer;
Parser *parser;

int main() {
    auto input = "expr=100*(1+3/24/5-(25+6))+3";
//    auto input = "1+25*6";
    lexer = new Lexer((uint8_t *) input);

    parser = new Parser(lexer);
    parser->parse();
    return 0;
}
