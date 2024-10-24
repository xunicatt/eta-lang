#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/tokens.h"

auto main() -> int32_t {
  // std::printf("REPL VER 0.1: eta\n");
  // std::string line;

  // while (true) {
  //   std::cout << "> ";
  //   std::getline(std::cin, line);
  //   if (line == ".exit") exit(0);

  //   Lexer l(line);

  //   while (l.token() != TEOF) {
  //     if (l.getlasttoken() == TUNKNOWN) {
  //       std::cout << "unknown token" << std::endl;
  //       break;
  //     }

  //     std::cout << "got token: " << TokenNames[l.getlasttoken()] <<
  //     std::endl;
  //   }
  // }

  std::string code;
  std::cout << "code> ";
  std::getline(std::cin, code);
  Lexer l("hello.n", code);
  l.token();
  ParseIdentifier(l);

  return 0;
}
