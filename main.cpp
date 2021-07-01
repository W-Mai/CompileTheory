#include <iostream>
#include <fstream>
#include "Lexer.h"

using namespace std;

Lexer *lexer;

int main() {
    string input_file_path = "/Users/esther/Documents/Projects/CompileTheory/test.c";
//    cin >> input_file_path;
    auto fin = ifstream (input_file_path);
    string input((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));;

    Token token{};
    lexer = new Lexer((uint8_t *) input.c_str());

    while (true) {
        token = lexer->next();
        if (token.syn == TOKEN_SYN::EOF_ or token.syn == TOKEN_SYN::ERROR) {
            if (token.syn == TOKEN_SYN::ERROR) {
                cout << endl << "ERROR: ";
                token.print();
            }
            break;
        }
        token.print();
        cout << endl;
    }
    return 0;
}
