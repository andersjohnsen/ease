#ifndef INTERPRETER
#define INTERPRETER

#include "vm/VirtualMachine.h"

class Interpreter : public VirtualMachine {
public:
  Interpreter() {}

  void execute(Expr *expr);

private:
  int evaluateExpr(Expr *expr);
};

#endif // INTERPRETER
