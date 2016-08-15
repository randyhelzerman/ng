#include <gtest/gtest.h>


#include <Parser.h>

using namespace ng;

TEST(ParserTest, test1)
{
  Parser parser;
  parser.parse("../test/ng.min");
}
