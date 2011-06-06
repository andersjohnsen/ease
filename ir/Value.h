#ifndef VALUE_H
#define VALUE_H

#include <string>

class Type;

class Value {
public:
  enum Kind {
    ConstantIntKind,
    BinOpInstKind,
    ReturnInstKind,
    GotoInstKind,
    BranchInstKind,
    BlockKind,
  };

protected:
  Value(Kind kind, const Type *type) : kind(kind), type(type) {}

public:
  const Type *getType() const { return type; }
  virtual std::string asString() const { return ""; }

  Kind getKind() const { return kind; }

  virtual bool isConstant() const { return false; }
  virtual bool isInstruction() const { return false; }

private:
  Kind kind;
  const Type *type;
};

#endif // VALUE_H
