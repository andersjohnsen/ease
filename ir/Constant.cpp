#include <sstream>

#include "ir/Constant.h"
#include "ir/Type.h"

ConstantInt::ConstantInt(uint64_t value) 
  : Constant(ConstantIntKind, Type::getIntType()), value(value) {
}

std::string ConstantInt::asString() const {
  std::stringstream str;
  str << value;
  return str.str();
}
