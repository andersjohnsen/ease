#ifndef FUNCTION_PASS_H
#define FUNCTION_PASS_H

#include <string>

class Block;
class Value;
class Function;
class Instruction;
class BinOpInst;

class FunctionPass {
protected:
  FunctionPass(const std::string &name) : name(name) {}

public:
  void runFunction(Function *);

protected:
  virtual void beginFunction(Function *) {}
  virtual void endFunction(Function *) {}
  virtual void beginBlock(Block *) {}
  virtual void endBlock(Block *) {}
  virtual void atBinOpInst(BinOpInst *) {}

protected:
  void atInstruction(Instruction *inst);

  void replaceValueBy(Value *oldValue, Value *nValue);

private:
  int position;
  Block *block;
  const std::string name;
};

class ConstantFoldingPass : public FunctionPass {
public:
  ConstantFoldingPass() : FunctionPass("ConstantFolding") {}


protected:
  void endBlock(Block *);
  void atBinOpInst(BinOpInst *binOp);
};

#endif // FUNCTION_PASS_H
