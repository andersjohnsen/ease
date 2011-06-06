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

Lexer::Lexer() {
  keywords["var"] = KWVar;
  keywords["if"] = KWIf;
  keywords["return"] = KWReturn;
}

static bool isNum(int c) {
  return c >= '0' && c <= '9';
}

static bool isLetter(int c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool isLetterOrNum(int c) {
  return isLetter(c) || isNum(c);
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

      case 'a': case 'b': case 'c': case 'd': case 'e':
      case 'f': case 'g': case 'h': case 'i': case 'j':
      case 'k': case 'l': case 'm': case 'n': case 'o':
      case 'p': case 'q': case 'r': case 's': case 't':
      case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
      case 'A': case 'B': case 'C': case 'D': case 'E':
      case 'F': case 'G': case 'H': case 'I': case 'J':
      case 'K': case 'L': case 'M': case 'N': case 'O':
      case 'P': case 'Q': case 'R': case 'S': case 'T':
      case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
      case '_': {
        std::string s;
        s += (char)c;
        while (input.good() && isLetterOrNum(input.peek()) ) {
          c = input.get();
          s += (char)c;
        }
        TokenKind kind = Identifier;
        if (keywords.find(s) != keywords.end())
          kind = keywords[s];
        tokens.push_back(Token(kind, pos, int(input.tellg()) - pos));
        break;
      }
      case ';':
        tokens.push_back(Token(SemiColon, pos, 1));
        break;

      case '=':
        tokens.push_back(Token(Equal, pos, 1));
        break;

      case '+':
        tokens.push_back(Token(Plus, pos, 1));
        break;

      case '*':
        tokens.push_back(Token(Star, pos, 1));
        break;

      case '(':
        tokens.push_back(Token(LParam, pos, 1));
        break;

      case ')':
        tokens.push_back(Token(RParam, pos, 1));
        break;

      case '{':
        tokens.push_back(Token(LBrace, pos, 1));
        break;

      case '}':
        tokens.push_back(Token(RBrace, pos, 1));
        break;

      default:
        std::cerr << "Warning: unhandled token " << c << " '" << char(c) << "'\n";
    }
  }

  tokens.push_back(Token(EndOfFile, input.tellg(), 0));

  return tokens;
}
