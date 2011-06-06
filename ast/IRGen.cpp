#include <iostream>

#include "ast/IRGen.h"
#include "ast/Expr.h"
#include "ast/Stmt.h"

#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Constant.h"

Function *IRGen::genFunction(std::vector<Stmt *> &stmts) {
  Function *function = new Function();
  Block *block = function->getEntryBlock();

  for (int i = 0; i < stmts.size(); i++) {
    block = fromStmt(block, stmts[i]);
  }

  return function;
}
  
Block *IRGen::fromStmt(Block *block, Stmt *stmt) {
  switch (stmt->getKind()) {
    case Stmt::Block: {
        BlockStmt *b = static_cast<BlockStmt *>(stmt);
        for (int i = 0; i < b->getStmts().size(); i++) {
          block = fromStmt(block, b->getStmts()[i]);
        }
        return block;
      }

    case Stmt::Var: {
        VarStmt *var = static_cast<VarStmt *>(stmt);
        Value *exprValue = fromExpr(block, var->getExpr());
        identifierMap[var->getName()] = exprValue;
        break;
      }

    case Stmt::Assign: {
        AssignStmt *assign = static_cast<AssignStmt *>(stmt);
        Value *exprValue = fromExpr(block, assign->getExpr());
        identifierMap[assign->getIdentifier()->getName()] = exprValue;
        break;
      }

    case Stmt::If: {
        IfStmt *ifStmt = static_cast<IfStmt *>(stmt);
        Value *ifValue = fromExpr(block, ifStmt->getExpr());
        Block *ifBlock = new Block("if", block->getFunction());
        Block *endIf = new Block("endIf", block->getFunction());
        BranchInst *ifBranch = new BranchInst(ifValue, ifBlock, endIf);
        block->addInstruction(ifBranch);
        block->getFunction()->valueUsed(ifValue, ifBranch);
        block->getFunction()->valueUsed(ifBlock, ifBranch);
        block->getFunction()->valueUsed(endIf, ifBranch);
        ifBlock = fromStmt(ifBlock, ifStmt->getIfStmt());
        GotoInst *gotoInst = new GotoInst(endIf);
        ifBlock->addInstruction(gotoInst);
        return endIf;
      }

    case Stmt::Return: {
        ReturnStmt *ret = static_cast<ReturnStmt*>(stmt);
        Value *value = fromExpr(block, ret->getExpr());
        ReturnInst *inst = new ReturnInst(value);
        block->addInstruction(inst);
        block->getFunction()->valueUsed(value, inst);
        break;
      }
  }
  return block;
}

Value *IRGen::fromExpr(Block *block, Expr *expr) {
  switch (expr->getKind()) {
    case Expr::Integer: {
        return new ConstantInt(
            static_cast<IntegerExpr *>(expr)->getValue());
      }
    case Expr::Identifier:
        return identifierMap[static_cast<IdentifierExpr *>(expr)->getName()];

    case Expr::BinOp: {
        BinOpExpr *binOp = static_cast<BinOpExpr *>(expr);
        Value *left = fromExpr(block, binOp->getLeft());
        Value *right = fromExpr(block, binOp->getRight());
        BinOpInst *inst = new BinOpInst(left, right, 
            (BinOpInst::Opcode)binOp->getOpcode());
        block->addInstruction(inst);
        block->getFunction()->valueUsed(left, inst);
        block->getFunction()->valueUsed(right, inst);
        return inst;
      }
  }
}
