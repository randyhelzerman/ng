#include <gtest/gtest.h>

#include <ng_token.h>
#include <ng_vector.h>
#include <ng_token_array.h>
#include <ng_token_array.t.h>

#include<stdbool.h>

const bool do_print = false;


TEST(NgTokenArrrayTest, Alloc)
{
  ng_token_array* tokens = 0x0;
  tokens = ng_token_array_new();
  EXPECT_NE((ng_token_array*)0x0, tokens);
  EXPECT_NE((ng_token_array*)0x0, tokens);
  EXPECT_EQ((const char*)0x0, tokens->string_);
  
  // expect it to have zero elements
  EXPECT_EQ(0, ng_token_array_size(tokens));
  
  ng_token_array_delete(&tokens);
  EXPECT_EQ((ng_token_array*)0x0, tokens);
}	    


TEST(NGTokenArrayTest, Dump)
{
  ng_token_array* tokens = ng_token_array_new();
  
  //                           012345678
  ng_token_array_set_string(tokens, "A -> 'a'B");
  
  ng_token_array_push_back(tokens, tokens->string_+0,tokens->string_+1, 10);
  EXPECT_EQ(1, ng_token_array_size(tokens));
  EXPECT_EQ(10, ng_token_array_at(tokens,0)->type_);
  
  ng_token_array_push_back(tokens, tokens->string_+2,tokens->string_+4, 11);
  EXPECT_EQ(2, ng_token_array_size(tokens));
  EXPECT_EQ(11, ng_token_array_at(tokens, 1)->type_);
  
  ng_token_array_push_back(tokens, tokens->string_+5,tokens->string_+8, 12);
  EXPECT_EQ(3, ng_token_array_size(tokens));
  EXPECT_EQ(12, ng_token_array_at(tokens, 2)->type_);
  
  ng_token_array_push_back(tokens, tokens->string_+8,tokens->string_+9, 10);
  EXPECT_EQ(4, ng_token_array_size(tokens));
  EXPECT_EQ(10, ng_token_array_at(tokens, 3)->type_);
  
  if (do_print) ng_token_array_dump(tokens);
  
  ng_token_array_delete(&tokens);
}
