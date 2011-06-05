#ifndef VALUE_H
#define VALUE_H

#include <string>

class Type;

class Value {
protected:
  Value(const Type *type) : type(type) {}

public:
  const Type *getType() const { return type; }
  virtual std::string asString() const { return ""; }

private:
  const Type *type;
};

#endif // VALUE_H
