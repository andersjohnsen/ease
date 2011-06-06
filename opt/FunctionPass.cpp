#include <iostream>

#include "opt/FunctionPass.h"

#include "ir/Function.h"
#include "ir/Constant.h"
#include "ir/Instruction.h"


void FunctionPass::runFunction(Function *func) {
  beginFunction(func);

  for (int i = 0; i < func->getBlocks().size(); i++) {
    block = func->getBlocks()[i];
    beginBlock(block);
    for (position = 0; position < block->getInstructions().size();) {
      Instruction *inst = block->getInstructions()[position];
      position++;
      atInstruction(inst);
    }
    endBlock(block);
  }

  endFunction(func);
}

void FunctionPass::atInstruction(Instruction *inst) {
  switch (inst->getKind()) {
    case Instruction::BinOpInstKind: {
        atBinOpInst(static_cast<BinOpInst *>(inst));
      }
  }
}

void FunctionPass::replaceValueBy(Value *oldValue, Value *nValue) {
  if (oldValue->isInstruction() && !nValue->isInstruction()) {
    block->removeInstruction(static_cast<Instruction *>(oldValue));
    position--;
    block->getFunction()->replaceValue(oldValue, nValue);
    return;
  }
  if (oldValue->isInstruction() && nValue->isInstruction()) {
    block->removeInstruction(static_cast<Instruction *>(oldValue));
    position--;
    block->getFunction()->replaceValue(oldValue, nValue);
    block->addInstruction(static_cast<Instruction *>(nValue));
  }
}

void ConstantFoldingPass::endBlock(Block *block) {
  Instruction *last = block->getInstructions().back();

  if (last->getKind() == Value::BranchInstKind) {
    BranchInst *branch = static_cast<BranchInst *>(last);
    if (!branch->getValue()->isConstant())
      return;
    
    if (static_cast<ConstantInt *>(branch->getValue())->getValue() == 0)
      replaceValueBy(branch, new GotoInst(branch->getElseBlock()));
    else
      replaceValueBy(branch, new GotoInst(branch->getIfBlock()));

    return;
  }

  if (block->getInstructions().size() == 1 
      && last->getKind() == Value::GotoInstKind) {
    GotoInst *gotoInst = static_cast<GotoInst *>(last);
    block->getFunction()->replaceValue(block, gotoInst->getBlock());
    return;
  }
}
  
void ConstantFoldingPass::atBinOpInst(BinOpInst *binOp) {
  Value *left = binOp->getLeft();
  Value *right = binOp->getRight();

  if (!left->isConstant() || !right->isConstant())
    return;

  Value *nValue;
  switch (binOp->getOpcode()) {
    case BinOpInst::Add: {
      nValue = new ConstantInt(
          static_cast<ConstantInt *>(left)->getValue() + 
          static_cast<ConstantInt *>(right)->getValue());
      break;
    }
    case BinOpInst::Mul: {
      nValue = new ConstantInt(
          static_cast<ConstantInt *>(left)->getValue() * 
          static_cast<ConstantInt *>(right)->getValue());
      break;
    }
  }

  replaceValueBy(binOp, nValue);
}
