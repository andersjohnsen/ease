#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <map>
#include <string>

class Function;
class Instruction;

class Block {
public:
  Block(Function *function) : function(function) {}

public:
  void addInstruction(Instruction *inst);

  void dump() const;

private:
  Function *function;
  std::vector<Instruction *> instructions;
};

class Function {
public:
  Function();

public:
  Block *getEntryBlock() const { return blocks.front(); }

  void setInstructionName(Instruction *inst);

  void dump() const;

private:
  std::vector<Block *> blocks;
  std::map<std::string, Instruction *> instructions;
};

#endif // FUNCTION_H
