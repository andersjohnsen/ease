#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <ostream>

class Operand {
public:
  enum Kind {
    Register,
    Stack,
    Memory,
    Value
  };
protected:
  Operand(Kind kind) : kind(kind) {}

public:
  Kind getKind() const { return kind; }
  virtual void dump() const = 0;

private:
  Kind kind;
};

class Register : public Operand {
public:
  enum Reg {
    EAX, 
    ECX, 
    EDX, 
    EBX, 
    ESP, 
    EBP, 
    ESI, 
    EDI
  };

public:
  Register(Reg reg) : Operand(Operand::Register), reg(reg) {}

public:
  Reg getReg() const { return reg; }
  void dump() const;

private:
  Reg reg;
};

class Stack: public Operand {
public:
  Stack(int offset) : Operand(Operand::Stack), offset(offset) {}

public:
  int getOffset() const { return offset; }
  void dump() const;

private:
  int offset;
};

class Value: public Operand {
public:
  Value(unsigned int data) : Operand(Operand::Value), data(data) {}

public:
  unsigned int getData() const { return data; }
  void dump() const;

private:
  unsigned int data;
};

class Inst {
public:
  enum Kind {
    Move,
    Add,
    Mul,
    Push,
    Pop
  };

protected:
  Inst(Kind kind) : kind(kind) {}

public:
  virtual void toMachineCode(std::ostream &out) const = 0;
  virtual void dump() const = 0;

private:
  Kind kind;
};

class MoveInst : public Inst {
public:
  MoveInst(Operand *to, Operand *from) 
    : Inst(Move), to(to), from(from) {}

public:
  void toMachineCode(std::ostream &out) const;
  void dump() const;

private:
  Operand *from, *to;
};

class AddInst : public Inst {
public:
  AddInst(Operand *value) 
    : Inst(Add), value(value) {}

public:
  void toMachineCode(std::ostream &out) const;
  void dump() const;

private:
  Operand *value;
};

class MulInst : public Inst {
public:
  MulInst(Operand *value) 
    : Inst(Mul), value(value) {}

public:
  void toMachineCode(std::ostream &out) const;
  void dump() const;

private:
  Operand *value;
};

class PushInst : public Inst {
public:
  PushInst(Register *reg) 
    : Inst(Push), reg(reg) {}

private:
  Register *reg;
};

class PopInst : public Inst {
public:
  PopInst(Register *reg) 
    : Inst(Pop), reg(reg) {}

private:
  Register *reg;
};

#endif // INSTRUCTIONS_H
