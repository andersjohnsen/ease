#include <sstream>
#include <iostream>

#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Type.h"

Block::Block(const std::string &name, Function *function) 
    : Value(BlockKind, Type::getVoidType()), name(name), function(function) {
  function->addBlock(this);
}

void Block::addInstruction(Instruction *inst) {
  instructions.push_back(inst);
  function->setInstructionName(inst);
}

void Block::removeInstruction(Instruction *inst) {
  for (std::vector<Instruction *>::iterator it = instructions.begin(),
                                            end = instructions.end();
       it != end; it++) {
    if (*it == inst) {
      instructions.erase(it);
      return;
    }
  }
}

std::string Block::asString() const {
  return "#" + name;
}
  
void Block::dump() const {
  std::cerr << " #" << name << ":\n";

  for (int i = 0; i < instructions.size(); i++) {
    instructions[i]->dump();
  }

  std::cerr << "\n";
}

Function::Function() {
  new Block("entry", this);
}
  
void Function::setInstructionName(Instruction *inst) {
  std::string name = inst->getName();
  if (name.empty())
    name = "tmp";

  int i = 0;
  std::string nameBuf = name;
  while (instructions.find(nameBuf) != instructions.end()) {
    std::stringstream str;
    str << name << i;
    nameBuf = str.str();
    i++;
  }

  instructions[nameBuf] = inst;
  inst->setName(nameBuf);
}

void Function::replaceValue(Value *old, Value *newValue) {
  for (std::multimap<Value *, Instruction *>::iterator 
       it = valueUses.equal_range(old).first,
       end = valueUses.equal_range(old).second;
       it != end; it++) {
    it->second->replaceValue(old, newValue);
    valueUsed(newValue, it->second);
  }
  valueUses.erase(old);
}

void Function::valueUsed(Value *v, Instruction *inst) {
  valueUses.insert(std::pair<Value *, Instruction *>(v, inst));
}
  
void Function::dump() const {
  std::cerr << "function ()\n";

  for (int i = 0; i < blocks.size(); i++) {
    blocks[i]->dump();
  }
}
