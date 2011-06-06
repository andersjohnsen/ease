#include <iostream>
#include <sstream>

#include "parser/Parser.h"
#include "ast/Expr.h"
#include "ast/Stmt.h"

Parser::Parser() {
  precedence.resize(NUM_TOKEN_KIND, -1);

  precedence[Plus] = 5;
  precedence[Star] = 7;
}

std::vector<Stmt *> Parser::parse(const std::vector<Token> &tokens, 
                                  std::istream &input) {
  this->tokens = tokens;
  this->inputStream = &input;
  position = 0;

  std::vector<Stmt *> stmts;

  while (!is_a(EndOfFile)) {
    stmts.push_back(parseStmt());
  }
  
  return stmts;
}

Stmt *Parser::parseStmt() {
  Token t = next();
  switch (t.kind) {
    case LBrace: {
      std::vector<Stmt *> stmts;
      while (!is_a(RBrace)) {
        stmts.push_back(parseStmt());
      }
      require(RParam);
      return new BlockStmt(stmts);
    }

    case KWVar: {
      std::string name = toString(require(Identifier));
      require(Equal);
      Expr *expr = parseExpr();
      require(SemiColon);
      return new VarStmt(name, expr);
    }

    case Identifier: {
      require(Equal);
      Expr *expr = parseExpr();
      require(SemiColon);
      return new AssignStmt(new IdentifierExpr(toString(t)), expr);
    }

    case KWIf: {
      require(LParam);
      Expr *expr = parseExpr();
      require(RParam);
      Stmt *stmt = parseStmt();
      return new IfStmt(expr, stmt);
    }

    case KWReturn: {
      Expr *expr = parseExpr();
      require(SemiColon);
      return new ReturnStmt(expr);
    }
  }
  return 0;
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

    case Identifier:
      return new IdentifierExpr(toString(next()));

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

Token Parser::require(TokenKind kind) {
  Token t = next();
  if (t.kind != kind)
    std::cerr << "Expected Identifier, got " << t.kind << "\n";
  return t;
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
