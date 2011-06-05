#include <iostream>

#include "ast/IRGen.h"
#include "ast/Expr.h"

#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Constant.h"

Function *IRGen::genFunction(std::vector<Expr *> &exprs) {
  Function *function = new Function();
  Block *entry = function->getEntryBlock();

  for (int i = 0; i < exprs.size(); i++) {
    fromExpr(entry, exprs[i]);
  }

  return function;
}

Value *IRGen::fromExpr(Block *block, Expr *expr) {
  switch (expr->getKind()) {
    case Expr::Integer: {
        return new ConstantInt(
            static_cast<IntegerExpr *>(expr)->getValue());
      }
    case Expr::BinOp: {
        BinOpExpr *binOp = static_cast<BinOpExpr *>(expr);
        Value *left = fromExpr(block, binOp->getLeft());
        Value *right = fromExpr(block, binOp->getRight());
        BinOpInst *inst = new BinOpInst(left, right, 
            (BinOpInst::Opcode)binOp->getOpcode());

        block->addInstruction(inst);
        return inst;
      }
  }
}
