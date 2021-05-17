#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

Lexer *lexer;
Parser *parser;

int main() {
    auto input = "100*(1+3/24-(25+6))+3";
    lexer = new Lexer((uint8_t *) input);

    parser = new Parser(lexer);
    parser->parse();
    return 0;
}
