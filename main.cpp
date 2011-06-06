#include <iostream>
#include <sstream>

#include "parser/Lexer.h"
#include "parser/Parser.h"

#include "ast/IRGen.h"

#include "ir/Function.h"

#include "opt/FunctionPass.h"

#include "vm/Interpreter.h"
#include "vm/X86Machine.h"

int main(int argc, char **argv) {
  std::string input = 
    "var x = 5 + 2 * 5 + 123 + 4 * 7;"
    "var y = x * x;"
    "if (y)"
    "  y = y + 1;"
    ""
    "return y;";

  Lexer lexer;

  std::istringstream inStream(input);
  std::vector<Token> tokens = lexer.lex(inStream);

  for (int i = 0; i < tokens.size(); i++) {
    tokens[i].dump();
    tokens[i].print(inStream);
    std::cerr << "\n";
  }

  Parser parser;
  std::vector<Stmt *> stmts = parser.parse(tokens, inStream);

  IRGen irgen;
  Function *function = irgen.genFunction(stmts);
  function->dump();

  ConstantFoldingPass constantFolding;
  constantFolding.runFunction(function);

  function->dump();

/*
  Interpreter interpreter;
  X86Machine x86Machine;
  for (int i = 0; i < exprs.size(); i++) {
    interpreter.execute(exprs[i]);
    x86Machine.execute(exprs[i]);
  }
*/
  return 0;
}
