#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <map>
#include <string>

#include "ir/Value.h"

class Function;
class Instruction;

class Block : public Value {
public:
  Block(const std::string &name, Function *function);

public:
  void addInstruction(Instruction *inst);
  void removeInstruction(Instruction *inst);
  const std::vector<Instruction *> &getInstructions() const {
    return instructions; 
  }

  Function *getFunction() const { return function; }

  std::string asString() const;

  void dump() const;

private:
  std::string name;
  Function *function;
  std::vector<Instruction *> instructions;
};

class Function {
public:
  Function();

public:
  Block *getEntryBlock() const { return blocks.front(); }
  void addBlock(Block *block) { blocks.push_back(block); }

  std::vector<Block *> getBlocks() const { return blocks; }

  void setInstructionName(Instruction *inst);

  void replaceValue(Value *old, Value *newValue);
  void valueUsed(Value *v, Instruction *inst);

  void dump() const;

private:
  std::vector<Block *> blocks;
  std::map<std::string, Instruction *> instructions;
  std::multimap<Value *, Instruction *> valueUses;
};

#endif // FUNCTION_H
