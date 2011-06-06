#ifndef STMT_H
#define STMT_H

class Expr;
class IdentifierExpr;

class Stmt {
public:
  enum Kind {
    Block,
    Var,
    Assign,
    If,
    Return
  };

protected:
  Stmt(Kind kind) : kind(kind) {}

public:
  Kind getKind() const { return kind; }

private:
  Kind kind;
};

class BlockStmt : public Stmt {
public:
  BlockStmt(const std::vector<Stmt *> &stmts) 
    : Stmt(Block), stmts(stmts) {}

public:
  const std::vector<Stmt *> &getStmts() { return stmts; }

private:
  std::vector<Stmt *> stmts;
};

class VarStmt : public Stmt {
public:
  VarStmt(const std::string &name, Expr *expr) 
    : Stmt(Var), name(name), expr(expr) {}

public:
  const std::string &getName() const { return name; }
  Expr *getExpr() const { return expr; }

private:
  std::string name;
  Expr *expr;
};

class AssignStmt : public Stmt {
public:
  AssignStmt(IdentifierExpr *identifier, Expr *expr) 
    : Stmt(Assign), identifier(identifier), expr(expr) {}

public:
  IdentifierExpr *getIdentifier() const { return identifier; }
  Expr *getExpr() const { return expr; }

private:
  IdentifierExpr *identifier;
  Expr *expr;
};

class IfStmt : public Stmt {
public:
  IfStmt(Expr *expr, Stmt *ifStmt) 
    : Stmt(If), expr(expr), ifStmt(ifStmt) {}

public:
  Expr *getExpr() const { return expr; }
  Stmt *getIfStmt() const { return ifStmt; }

private:
  Expr *expr;
  Stmt *ifStmt;
};

class ReturnStmt : public Stmt {
public:
  ReturnStmt(Expr *expr) 
    : Stmt(Return), expr(expr) {}

public:
  Expr *getExpr() const { return expr; }

private:
  Expr *expr;
};

#endif // STMT_H
