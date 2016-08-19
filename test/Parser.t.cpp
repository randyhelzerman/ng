#include <gtest/gtest.h>

#include <Parser.h>

#include <Nfa.h>

using namespace ng;

TEST(ParserTest, test1)
{
  Parser parser;
  parser.parse("../test/ng.min");
  parser.dump();

  Nfa nfa;
  parser.build(nfa);
  nfa.dump();
}
