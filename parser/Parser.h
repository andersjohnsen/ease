#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "parser/Lexer.h"

class Expr;

class Parser {
public:
  Parser();

public:
  std::vector<Expr *> parse(const std::vector<Token> &tokens, std::istream &input);

private:
  Expr *parseExpr(int i = 0);
  Expr *parsePrimaryExpr();

  Token next();
  Token peek(int o = 0);
  bool is_a(TokenKind kind, int o = 0);

  std::string toString(Token t);
  int toInt(Token t);

private:
  int position;
  std::vector<Token> tokens;
  std::vector<int> precedence;
  std::istream *inputStream;
};

#endif // PARSER_H
