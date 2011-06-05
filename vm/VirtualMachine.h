#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

class Expr;

class VirtualMachine {
protected:
  VirtualMachine() {}

public:
  virtual void execute(Expr *expr) = 0;
};

#endif // VIRTUAL_MACHINE_H
