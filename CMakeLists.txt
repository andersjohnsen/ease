PROJECT(Ease)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(
  ease
  main.cpp
  parser/Lexer.cpp
  parser/Parser.cpp

  ast/IRGen.cpp

  ir/Type.cpp
  ir/Constant.cpp
  ir/Instruction.cpp
  ir/Function.cpp

  opt/FunctionPass.cpp

  vm/Interpreter.cpp
  vm/X86Machine.cpp
  vm/Instructions.cpp
  )
