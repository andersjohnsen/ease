#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

#include "ir/Value.h"

class Block;

class Instruction : public Value {
protected:
  Instruction(Kind kind, const Type *type) : Value(kind, type) {}

public:
  void setName(std::string &name) { this->name = name; }
  const std::string &getName() const { return name; }

  virtual void dump() const = 0;

  std::string asString() const { return getName(); }

  bool isInstruction() const { return true; }

  virtual void replaceValue(Value *old, Value *v) = 0;

private:
  std::string name;
};

class BinOpInst: public Instruction {
public:
  enum Opcode {
    Add,
    Minus,
    Mul,
    Div,
    Rem
  };

public:
  BinOpInst(Value *left, Value *right, Opcode opcode);

public:
  Value *getLeft() const { return left; }
  Value *getRight() const { return right; }
  Opcode getOpcode() const { return opcode; }

  void setLeft(Value *v) { left = v; }
  void setRight(Value *v) { right = v; }

  void replaceValue(Value *old, Value *v);

  void dump() const;

private:
  Value *left, *right;
  Opcode opcode;
};

class ReturnInst : public Instruction {
public:
  ReturnInst(Value *value);

public:
  Value *getValue() const { return value; }

  void replaceValue(Value *old, Value *v);

  void dump() const;

private:
  Value *value;
};

class GotoInst : public Instruction {
public:
  GotoInst(Block *block);

public:
  Block *getBlock() const { return block; }

  void replaceValue(Value *old, Value *v);

  void dump() const;

private:
  Block *block;
};

class BranchInst : public Instruction {
public:
  BranchInst(Value *value, Block *ifBlock, Block *elseBlock);

public:
  Value *getValue() const { return value; }
  Block *getIfBlock() const { return ifBlock; }
  Block *getElseBlock() const { return elseBlock; }

  void replaceValue(Value *old, Value *v);

  void dump() const;

private:
  Value *value;
  Block *ifBlock, *elseBlock;
};

#endif // INSTRUCTION_H
