#include <iostream>

#include "vm/Interpreter.h"

#include "ast/Expr.h"

void Interpreter::execute(Expr *expr) {
  int result = evaluateExpr(expr);
  std::cerr << "Result of interpreter: " << result << "\n";
}


int Interpreter::evaluateExpr(Expr *expr) {
  switch (expr->getKind()) {
    case Expr::Integer:
      return static_cast<IntegerExpr *>(expr)->getValue();

    case Expr::BinOp: {
      BinOpExpr *binOp = static_cast<BinOpExpr *>(expr);
      int left = evaluateExpr(binOp->getLeft());
      int right = evaluateExpr(binOp->getRight());
      switch (binOp->getOpcode()) {
        case BinOpExpr::Add: return left + right;
        case BinOpExpr::Multiply: return left * right;
        default:
          std::cerr << "Invalid opcode in interpreter\n";
      }
      break;
    }

    default:
      std::cerr << "Invalid expression in interpreter\n";
  }

  return -1;
}
