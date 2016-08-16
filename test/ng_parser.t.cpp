#include <gtest/gtest.h>

// The module we are testing
#include <ng_parser.h>
#include <ng_parser.t.h>

// system includes
#include<stdbool.h>

// library includes
#include <ng_token.h>
#include <ng_token_array.h>

// utility includes
#include <ng_util_io.h>

const bool do_dump=true;


TEST(NgNfaParserTest, Alloc)
{
  // allocate a parser
  ng_parser* parser = 0x0;
  parser = ng_parser_new();
  EXPECT_NE((ng_parser*)0x0, parser);
  
  // 
  ng_parser_delete(&parser);
  EXPECT_EQ((ng_parser*)0x0, parser);
}


TEST(NgNfaParserTest, tokenizersP)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "A -> 'a'B  B -> 'b'C  C->'c'");
  
  if (do_dump) ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence1)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "\n");
  EXPECT_EQ(1, ng_token_array_size(parser->tokens_));
  
  ng_token* token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_SENTENCE, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence2)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "\n\n");
  EXPECT_EQ(1, ng_token_array_size(parser->tokens_));
  
  ng_token* token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_PP, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence3)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "\nblaher");
  EXPECT_EQ(2, ng_token_array_size(parser->tokens_));
  
  ng_token* token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_SENTENCE, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence4)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "\n\n  balther");
  EXPECT_EQ(2, ng_token_array_size(parser->tokens_));
  
  ng_token* token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_PP, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence5)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "# this is a comment\n\n");
  EXPECT_EQ(2, ng_token_array_size(parser->tokens_));
  
  ng_token* token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_COMMENT, token->type_);
  
  token = ng_token_array_at(parser->tokens_,1);
  EXPECT_EQ(NG_PARSER_PP, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}

TEST(NgNfaParserTest, toksentence6)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, ": # this is a comment\n\n");
  EXPECT_EQ(3, ng_token_array_size(parser->tokens_));
  
  ng_token* token;
  
  token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_COLON, token->type_);
  
  token = ng_token_array_at(parser->tokens_,1);
  EXPECT_EQ(NG_PARSER_COMMENT, token->type_);
  
  token = ng_token_array_at(parser->tokens_,2);
  EXPECT_EQ(NG_PARSER_PP, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence7)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "\\ # this is a comment\n\n");
  EXPECT_EQ(3, ng_token_array_size(parser->tokens_));
  
  ng_token* token;
  
  token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_BSLASH, token->type_);
  
  token = ng_token_array_at(parser->tokens_,1);
  EXPECT_EQ(NG_PARSER_COMMENT, token->type_);
  
  token = ng_token_array_at(parser->tokens_,2);
  EXPECT_EQ(NG_PARSER_PP, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence8)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "/ # this is a comment\n");
  EXPECT_EQ(3, ng_token_array_size(parser->tokens_));
  
  ng_token* token;
  
  token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_DIV, token->type_);
  
  token = ng_token_array_at(parser->tokens_,1);
  EXPECT_EQ(NG_PARSER_COMMENT, token->type_);
  
  token = ng_token_array_at(parser->tokens_,2);
  EXPECT_EQ(NG_PARSER_SENTENCE, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, toksentence9)
{
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, "--> # this is a comment\n");
  EXPECT_EQ(3, ng_token_array_size(parser->tokens_));
  
  ng_token* token;
  
  token = ng_token_array_at(parser->tokens_,0);
  EXPECT_EQ(NG_PARSER_PROD, token->type_);
  
  token = ng_token_array_at(parser->tokens_,1);
  EXPECT_EQ(NG_PARSER_COMMENT, token->type_);
  
  token = ng_token_array_at(parser->tokens_,2);
  EXPECT_EQ(NG_PARSER_SENTENCE, token->type_);
  
  ng_parser_dump(parser);
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, tokfile1)
{
  // read in file
  char* buf=0x0;
  loadFileIntoBuffer("../test/ng.ng", &buf);
  
  // create parser to tokenize it
  ng_parser* parser = ng_parser_new();
  
  ng_parser_tokenize(parser, buf);
  
  printf("dumping parser\n");
  ng_parser_dump(parser);
  printf("done dumping parser\n");
  
  ng_parser_delete(&parser);
}


TEST(NgNfaParserTest, min_parse_1)
{
  // read in file
  char* buf=0x0;
  loadFileIntoBuffer("../test/ng.min", &buf);
  
  // create parser to tokenize it
  ng_parser* parser = ng_parser_new();
  
  ng_parser_min_parse(parser, buf);
  
  printf("dumping parser\n");
  ng_parser_dump(parser);
  printf("done dumping parser\n");
  
  ng_parser_delete(&parser);
}

