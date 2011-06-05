#include <iostream>

#include "ir/Instruction.h"

BinOpInst::BinOpInst(Value *left, Value *right, Opcode opcode) 
  : Instruction(left->getType()), left(left), right(right), 
    opcode(opcode) {
}

void BinOpInst::dump() const {

  std::cerr << "  " << getName() << " := " 
            << left->asString() << " ";
  
  switch (opcode) {
    case Add: std::cerr << "+"; break;
    case Mul: std::cerr << "*"; break;
  }

  std::cerr << " " << right->asString() << "\n";
}
