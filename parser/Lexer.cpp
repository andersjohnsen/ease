#include "parser/Lexer.h"

#include <iostream>

void Token::dump() {
  std::cerr << "Token (" << kind << ", " << position << ", " << length << ")\n";
}

std::string Token::toString(std::istream &input) {
  std::string s;

  input.clear();
  input.seekg(position, std::istream::beg);
  for (int i = 0; i < length; i++)
    s += char(input.get());

  return s;
}

void Token::print(std::istream &input) {
  std::cerr << toString(input);
}

static bool isNum(int c) {
  return c >= '0' && c <= '9';
}

std::vector<Token> Lexer::lex(std::istream &input) {
  std::vector<Token> tokens;

  while (input.good()) {
    int pos = input.tellg();
    int c = input.get(); 
    if (c < 0)
      break;

    switch (c) {
      // Whitespaces
      case ' ':
      case '\n':
      case '\0':
        break;

      // numbers
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        while (input.good() && isNum(input.peek()) ) {
          input.get();
        }
        tokens.push_back(Token(Number, pos, int(input.tellg()) - pos));
        break;

      case '+':
        tokens.push_back(Token(Plus, pos, 1));
        break;

      case '*':
        tokens.push_back(Token(Star, pos, 1));
        break;

      default:
        std::cerr << "Warning: unhandled token " << c << " '" << char(c) << "'\n";
    }
  }

  tokens.push_back(Token(EndOfFile, input.tellg(), 0));

  return tokens;
}
