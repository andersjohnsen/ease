#include <iostream> 
#include <sstream> 

#include "vm/Instructions.h"

static unsigned char regRM(const Operand *to, const Operand *from) {
  unsigned char val = 0;
  val |= static_cast<const Register *>(to)->getReg();
  val |= (static_cast<const Register *>(to)->getReg() + 8) << 4;
  return val;
}

static unsigned char stackOffset(const Operand *stack) {
  return 0x100 - static_cast<const Stack *>(stack)->getOffset() * 4;
}

static unsigned int valueData(const Operand *value) {
  return static_cast<const Value *>(value)->getData();
}

void MoveInst::toMachineCode(std::ostream &out) const {
  if (to->getKind() == Operand::Register && from->getKind() == Operand::Register) {
    out << (unsigned char)0x48;
    out << (unsigned char)regRM(to, from);
    return;
  }

  if (to->getKind() == Operand::Stack && from->getKind() == Operand::Value) {
    out << (unsigned char)0xC7;
    out << (unsigned char)0x44;
    out << (unsigned char)0x24;
    out << stackOffset(to);
    out << (unsigned char)valueData(from);
    out << (unsigned char)(valueData(from) >> 8);
    out << (unsigned char)(valueData(from) >> 16);
    out << (unsigned char)(valueData(from) >> 24);
    return;
  }

  if (to->getKind() == Operand::Register && from->getKind() == Operand::Stack) {
    out << (unsigned char)0x8B;
    out << (unsigned char)0x44;
    out << (unsigned char)0x24;
    out << stackOffset(from);
    return;
  }

  if (to->getKind() == Operand::Stack && from->getKind() == Operand::Register) {
    out << (unsigned char)0x89;
    out << (unsigned char)0x44;
    out << (unsigned char)0x24;
    out << stackOffset(to);
    return;
  }

  std::cerr << "Unhandled MoveInst\n";
}

void AddInst::toMachineCode(std::ostream &out) const {
  if (value->getKind() == Operand::Stack) {
    out << (unsigned char)0x03;
    out << (unsigned char)0x44;
    out << (unsigned char)0x24;
    out << stackOffset(value);
    return;
  }

  std::cerr << "Unhandled AddInst\n";
}

void MulInst::toMachineCode(std::ostream &out) const {
  if (value->getKind() == Operand::Stack) {
    out << (unsigned char)0x0F;
    out << (unsigned char)0xAF;
    out << (unsigned char)0x44;
    out << (unsigned char)0x24;
    out << stackOffset(value);
    return;
  }

  std::cerr << "Unhandled MulInst\n";
}

void Register::dump() const {
  switch (reg) {
    case EAX: std::cerr << "Reg: EAX"; return;
    case ECX: std::cerr << "Reg: ECX"; return;
    case EDX: std::cerr << "Reg: EDX"; return;
    case EBX: std::cerr << "Reg: EBX"; return;
    case ESP: std::cerr << "Reg: ESP"; return;
    case EBP: std::cerr << "Reg: EBP"; return;
    case ESI: std::cerr << "Reg: ESI"; return;
    case EDI: std::cerr << "Reg: EDI"; return;
  }          
}

void Stack::dump() const {
  std::ostringstream str;
  str << (void *)stackOffset(this);
  std::cerr << "Stack: " << str.str();
}

void Value::dump() const {
  std::cerr << "Value: " << data;
}

void MoveInst::dump() const {
  std::cerr << "MoveInst: (";
  to->dump();
  std::cerr << ") <- (";
  from->dump();
  std::cerr << ")\n";
}

void AddInst::dump() const {
  std::cerr << "AddInst: (Reg: EAX) <- (Reg: EAX) + (";
  value->dump();
  std::cerr << ")\n";
}

void MulInst::dump() const {
  std::cerr << "MulInst: (Reg: EAX) <- (Reg: EAX) * (";
  value->dump();
  std::cerr << ")\n";
}
