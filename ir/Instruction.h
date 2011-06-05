#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

#include "ir/Value.h"

class Instruction : public Value {
protected:
  Instruction(const Type *type) : Value(type) {}

public:
  void setName(std::string &name) { this->name = name; }
  const std::string &getName() const { return name; }

  virtual void dump() const = 0;

  std::string asString() const { return getName(); }

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
  void dump() const;

  Value *left, *right;
  Opcode opcode;
};

#endif // INSTRUCTION_H
