#include <sstream>
#include <iostream>

#include "ir/Function.h"
#include "ir/Instruction.h"

void Block::addInstruction(Instruction *inst) {
  instructions.push_back(inst);
  function->setInstructionName(inst);
}
  
void Block::dump() const {
  std::cerr << " #block:\n";

  for (int i = 0; i < instructions.size(); i++) {
    instructions[i]->dump();
  }

  std::cerr << "\n";
}

Function::Function() {
  blocks.push_back(new Block(this));
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
  
void Function::dump() const {
  std::cerr << "function ()\n";

  for (int i = 0; i < blocks.size(); i++) {
    blocks[i]->dump();
  }
}
