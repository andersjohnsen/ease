#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <map>
#include <istream>

enum TokenKind {
  EndOfFile,

  Identifier,
  Number,

  SemiColon,
  Equal,

  Plus,
  Star,

  LParam,
  RParam,
  LBrace,
  RBrace,

  KWVar,
  KWIf,
  KWReturn,

  NUM_TOKEN_KIND
};

struct Token{
  Token(TokenKind kind, int position, int length) 
    : kind(kind), position(position), length(length) {}

  void dump();
  std::string toString(std::istream &input);
  void print(std::istream &input);

  TokenKind kind;
  int position;
  int length;
};

class Lexer {
public:
  Lexer();
  
public:
  std::vector<Token> lex(std::istream &buffer);

private:
  std::map<std::string, TokenKind> keywords;
};

#endif // LEXER_H
