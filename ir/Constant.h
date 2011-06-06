#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>

#include "ir/Value.h"

class Constant : public Value {
protected:
  Constant(Kind kind, const Type *type) : Value(kind, type) {}

public:
  bool isConstant() const { return true; }
};

class ConstantInt : public Constant {
public:
  ConstantInt(uint64_t value);

public:
  std::string asString() const;

  uint64_t getValue() const { return value; }

private:
  uint64_t value;
};

#endif // CONSTANT_H
