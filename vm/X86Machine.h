#ifndef X86_MACHINE_H
#define X86_MACHINE_H

#include <vector>

#include "vm/VirtualMachine.h"

class Operand;
class Inst;

class X86Machine : public VirtualMachine {
public:
  X86Machine() {}

public:
  void execute(Expr *expr);

private:
  Operand *buildExpr(Expr *expr, std::vector<Inst *> &ins, int &stackNr);
};

#endif // X86_MACHINE_H
