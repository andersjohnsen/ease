#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "vm/X86Machine.h"
#include "vm/Instructions.h"

#include "ast/Expr.h"

typedef int (*func)();

void X86Machine::execute(Expr *expr) {
  size_t pagesize = getpagesize();
  void *nData = malloc(pagesize * 2);
  void *oldPos = nData;
  nData = (void *)(((long)nData + pagesize-1) & ~(pagesize-1));
  if(mprotect(nData, pagesize, PROT_READ|PROT_EXEC|PROT_WRITE)) {
    std::cout << "mprotect failed\n";
    return;
  }
  std::vector<Inst *> instructions;
  int stackNr = 0;
  buildExpr(expr, instructions, stackNr);
  
  std::ostringstream str;
  
  for (int i = 0; i < instructions.size(); i++) {
    Inst *inst = instructions[i];
    inst->dump();
  }
  for (int i = 0; i < instructions.size(); i++) {
    Inst *inst = instructions[i];
    std::ostringstream s;
    inst->toMachineCode(s);
    for (int i = 0; i < s.str().size(); i++) {
      std::cerr << (void *)(s.str()[i] & 0xFF) << " ";
    }
    std::cerr << "\n";
    str << s.str();
  }

  str << (unsigned char)0xC3;
  std::string data = str.str();
  const char *funcData = data.c_str();


  memcpy(nData, funcData, data.size());

  int result = ((func)nData)();
  std::cerr << "Result of X86Machine: " << result << "\n";
}

Operand *X86Machine::buildExpr(Expr *expr, std::vector<Inst *> &ins, int &stackNr) {
  switch (expr->getKind()) {
    case Expr::Integer:
      ins.push_back(
          new MoveInst(
            new Stack(++stackNr),
            new Value(static_cast<IntegerExpr *>(expr)->getValue())));
      return new Stack(stackNr);

    case Expr::BinOp: {
      BinOpExpr *binOp = static_cast<BinOpExpr *>(expr);
      Operand *left = buildExpr(binOp->getLeft(), ins, stackNr);
      Operand *right = buildExpr(binOp->getRight(), ins, stackNr);

      ins.push_back(
          new MoveInst(
            new Register(Register::EAX),
            left));

      switch (binOp->getOpcode()) {
        case BinOpExpr::Add:
          ins.push_back(
              new AddInst(
                right));
          break;

        case BinOpExpr::Multiply:
          ins.push_back(
              new MulInst(
                right));
          break;

        default:
          std::cerr << "Invalid opcode in x86 machine\n";
      }

      ins.push_back(
          new MoveInst(
            new Stack(++stackNr),
            new Register(Register::EAX)));

      return new Stack(stackNr);
      break;
    }

    default:
      std::cerr << "Invalid expression in x86 machine\n";
  }
  return 0;
}
