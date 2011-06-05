#include <iostream>
#include <sstream>

#include "parser/Lexer.h"
#include "parser/Parser.h"

#include "ast/IRGen.h"

#include "ir/Function.h"

#include "vm/Interpreter.h"
#include "vm/X86Machine.h"

int main(int argc, char **argv) {
  std::string input = 
    "5 + 2 * 5 + 123 + 4 * 7";
                      
  std::cout << input;

  Lexer lexer;

  std::istringstream inStream(input);
  std::vector<Token> tokens = lexer.lex(inStream);

  for (int i = 0; i < tokens.size(); i++) {
    tokens[i].dump();
    tokens[i].print(inStream);
    std::cerr << "\n";
  }

  Parser parser;
  std::vector<Expr *> exprs = parser.parse(tokens, inStream);

  IRGen irgen;
  Function *function = irgen.genFunction(exprs);
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
