#ifndef IR_GEN_H
#define IR_GEN_H

#include <vector>
#include <map>
#include <string>

class Stmt;
class Expr;

class Value;
class Instruction;
class Block;
class Function;

class IRGen {
public:
  IRGen() {}

public:
  Function *genFunction(std::vector<Stmt *> &stmts);
  Block *fromStmt(Block *block, Stmt *stmt);
  Value *fromExpr(Block *block, Expr *expr);

private:
  std::map<std::string, Value *> identifierMap;
};

#endif // IR_GEN_H
