#ifndef IR_GEN_H
#define IR_GEN_H

#include <vector>

class Expr;

class Value;
class Instruction;
class Block;
class Function;

class IRGen {
public:
  IRGen() {}

public:
  Function *genFunction(std::vector<Expr *> &exprs);
  Value *fromExpr(Block *block, Expr *expr);
};

#endif // IR_GEN_H
