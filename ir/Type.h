#ifndef TYPE_H
#define TYPE_H

class IntegerType;

class Type {
protected:
  Type() {}

public:
  static const IntegerType *getIntType() { return intType; }

private:
  static const IntegerType *intType;
};

class IntegerType : public Type {
public:
  IntegerType() {}
};

#endif // TYPE_H
