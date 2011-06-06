#ifndef TYPE_H
#define TYPE_H

class IntegerType;

class Type {
protected:
  Type() {}

public:
  static const IntegerType *getIntType() { return intType; }
  static const Type *getVoidType() { return voidType; }

private:
  static const IntegerType *intType;
  static const Type *voidType;
};

class IntegerType : public Type {
public:
  IntegerType() {}
};

#endif // TYPE_H
