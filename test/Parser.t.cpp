#include <gtest/gtest.h>

#include <Parser.h>

#include <Nfa.h>

namespace ng {

TEST(ParserTest, test1)
{
  Parser parser;
  parser.parse("../test/ng.min");
  parser.dump();
  
  Nfa nfa;
  parser.build(nfa);
  nfa.dump();
}

TEST(ParserTest, test2)
{
  Parser parser;
  parser.parse("../test/edge_cases.ng/merge.ng");
  parser.dump();
  
  Nfa nfa;
  parser.build(nfa);
  nfa.dump();
}


TEST(ParserTest, test3)
{
  Parser parser;
  parser.parse("../test/edge_cases.ng/empty.ng");
  parser.dump();
  
  EXPECT_EQ(1, parser.nonTerminals_.size());
  EXPECT_EQ(1, parser.stateInfos_.size());
  
  Nfa nfa;
  parser.build(nfa);
  EXPECT_EQ(1, nfa.stateInfos_.size());
  nfa.dump();
}


TEST(ParserTest, test4)
{
  Parser parser;
  parser.parse("../test/edge_cases.ng/1_lang.ng");
  parser.dump();
  
  EXPECT_EQ(2, parser.nonTerminals_.size());
  EXPECT_EQ(2, parser.stateInfos_.size());
  
  Nfa nfa;
  parser.build(nfa);
  EXPECT_EQ(2, nfa.stateInfos_.size());
  nfa.dump();
}
}
