#include <iostream>
#include <sstream>

#include "parser/Parser.h"
#include "ast/Expr.h"

Parser::Parser() {
  precedence.resize(NUM_TOKEN_KIND, -1);

  precedence[Plus] = 5;
  precedence[Star] = 7;
}

std::vector<Expr *> Parser::parse(const std::vector<Token> &tokens, 
                                  std::istream &input) {
  this->tokens = tokens;
  this->inputStream = &input;
  position = 0;

  std::vector<Expr *> exprs;

  while (!is_a(EndOfFile)) {
    exprs.push_back(parseExpr());
  }
  
  return exprs;
}

Expr *Parser::parseExpr(int p) {
  Expr *left = parsePrimaryExpr();
  Token t = peek();
  while (precedence[t.kind] >= p) {
    Token op = next();

    BinOpExpr::Opcode opcode;
    switch (op.kind) {
      case Plus: opcode = BinOpExpr::Add; break;
      case Star: opcode = BinOpExpr::Multiply; break;
      default: std::cerr << "Invalid opcode " << op.kind << "\n";
    }

    Expr *right = parseExpr(precedence[t.kind]);
    left = new BinOpExpr(left, right, opcode);
    t = peek();
  }

  return left;
}

Expr *Parser::parsePrimaryExpr() {
  switch (peek().kind) {
    case Number:
      return new IntegerExpr(toInt(next()));

    default:
      std::cerr << "Error: Invalid expression token " << next().kind << "\n";
  }
  return 0;
}


Token Parser::next() {
  return tokens[position++];
}

Token Parser::peek(int o) {
  return tokens[position + o];
}

bool Parser::is_a(TokenKind kind, int o) {
  return peek().kind == kind;
}

std::string Parser::toString(Token t) {
  return t.toString(*inputStream);
}

int Parser::toInt(Token t) {
  int value;

  std::string str = toString(t);
  std::stringstream s(str);

  s >> value;
  return value;
}
