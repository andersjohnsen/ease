#ifndef EXPR_H
#define EXPR_H

class Expr {
public:
  enum Kind {
    Integer,
    BinOp,
  };

protected:
  Expr(Kind kind) : kind(kind) {}

public:
  Kind getKind() const { return kind; }

private:
  Kind kind;
};

class IntegerExpr : public Expr {
public:
  IntegerExpr(int value) : Expr(Integer), value(value) {}

public:
  int getValue() const { return value; }

private:
  int value;
};

class BinOpExpr : public Expr {
public:
  enum Opcode {
    Add,
    Minus,
    Multiply,
    Divide
  };

public:
  BinOpExpr(Expr *left, Expr *right, Opcode opcode) : 
    Expr(BinOp), left(left), right(right), opcode(opcode) {}

public:
  Expr *getLeft() const { return left; }
  Expr *getRight() const { return right; }
  Opcode getOpcode() const { return opcode; }

private:
  Expr *left, *right;
  Opcode opcode;
};

#endif // EXPR_H
