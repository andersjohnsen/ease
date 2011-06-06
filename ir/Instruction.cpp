#include <iostream>

#include "ir/Instruction.h"
#include "ir/Function.h"
#include "ir/Type.h"

BinOpInst::BinOpInst(Value *left, Value *right, Opcode opcode) 
  : Instruction(BinOpInstKind, left->getType()), left(left), right(right), 
    opcode(opcode) {
}

void BinOpInst::replaceValue(Value *old, Value *v) {
  if (left == old)
    left = v;
  if (right == old)
    right = v;
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

ReturnInst::ReturnInst(Value *value) 
  : Instruction(ReturnInstKind, value->getType()), value(value) {
}

void ReturnInst::replaceValue(Value *old, Value *v) {
  if (value == old)
    value = v;
}

void ReturnInst::dump() const {
  std::cerr << "  ret " << value->asString() << "\n";
}

GotoInst::GotoInst(Block *block) 
  : Instruction(GotoInstKind, Type::getVoidType()), block(block) {
}

void GotoInst::replaceValue(Value *old, Value *v) {
}

void GotoInst::dump() const {
  std::cerr << "  goto " << block->asString() << "\n";
}
  
BranchInst::BranchInst(Value *value, Block *ifBlock, Block *elseBlock) 
  : Instruction(BranchInstKind, Type::getVoidType()), 
    value(value), ifBlock(ifBlock), elseBlock(elseBlock) {
}

void BranchInst::replaceValue(Value *old, Value *v) {
  if (value == old)
    value = v;
  if (ifBlock == old)
    ifBlock = static_cast<Block *>(v);
  if (elseBlock == old)
    elseBlock = static_cast<Block *>(v);
}

void BranchInst::dump() const {
  std::cerr << "  branch " << value->asString() 
            << " if " << ifBlock->asString()
            << " else " << elseBlock->asString()
            << "\n";
}
