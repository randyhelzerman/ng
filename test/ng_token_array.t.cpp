#include <gtest/gtest.h>

#include <ng_token_array.h>
#include <ng_token_array.t.h>

#include<stdbool.h>

const bool do_print = false;


TEST(NgTokenArrrayTest, Alloc)
{
  ng_token_array_t* tokens = 0x0;
  tokens = ng_token_array_new();
  EXPECT_NE((ng_token_array_t*)0x0, tokens);
  EXPECT_NE((ng_token_array_t*)0x0, tokens);
  EXPECT_EQ((const char*)0x0, tokens->string_);
  
  ng_token_array_delete(&tokens);
  EXPECT_EQ((ng_token_array_t*)0x0, tokens);
}
	    

TEST(NGTokenArrayTest, Dump)
{
  ng_token_array_t* tokens = ng_token_array_new();
  
  //                           012345678
  ng_token_array_set_string(tokens, "A -> 'a'B");
  
  ng_token_array_push_back(tokens, 0,1, 10);
  ng_token_array_push_back(tokens, 2,4, 11);
  ng_token_array_push_back(tokens, 5,8, 12);
  ng_token_array_push_back(tokens, 8,9, 10);
  
  if (do_print) ng_token_array_dump(tokens);
  
  ng_token_array_delete(&tokens);
}
