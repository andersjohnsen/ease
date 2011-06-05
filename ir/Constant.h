#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>

#include "ir/Value.h"

class Constant : public Value {
protected:
  Constant(const Type *type) : Value(type) {}
};

class ConstantInt : public Constant {
public:
  ConstantInt(uint64_t value);

public:
  std::string asString() const;

private:
  uint64_t value;
};

#endif // CONSTANT_H
