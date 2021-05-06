#include <iostream>
#include "Lexer.h"

using namespace std;

Lexer *lexer;

int main() {
    auto input = "int main(){"
                 "  int a = 3233;"
                 "  if(a>1){"
                 "      char b = 4"
                 "  }else{"
                 "      while(b==3);"
                 "  }"
                 "}";

    Token token{};
    lexer = new Lexer((uint8_t *) input);

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
