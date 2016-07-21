#include <gtest/gtest.h>

#include <ng_ascii_util.h>

#include<stdbool.h>

TEST(NgAsciiUtilTest, white_space)
{
  EXPECT_EQ(true, ng_ascii_util_is_white_space(' '));
  EXPECT_EQ(true, ng_ascii_util_is_white_space('\t'));
  EXPECT_EQ(true, ng_ascii_util_is_white_space('\n'));
  
  EXPECT_NE(true, ng_ascii_util_is_white_space('a'));
  EXPECT_NE(true, ng_ascii_util_is_white_space('z'));
  EXPECT_NE(true, ng_ascii_util_is_white_space('4'));
}


TEST(NgAsciiUtilTest, lower_case)
{
  EXPECT_EQ(true, ng_ascii_util_is_lower_case('a'));
  EXPECT_EQ(true, ng_ascii_util_is_lower_case('m'));
  EXPECT_EQ(true, ng_ascii_util_is_lower_case('z'));
  
  EXPECT_NE(true, ng_ascii_util_is_lower_case('A'));
  EXPECT_NE(true, ng_ascii_util_is_lower_case('N'));
  EXPECT_NE(true, ng_ascii_util_is_lower_case('Z'));
  EXPECT_NE(true, ng_ascii_util_is_lower_case('1'));
  EXPECT_NE(true, ng_ascii_util_is_lower_case(' '));
  EXPECT_NE(true, ng_ascii_util_is_lower_case('\n'));
}


TEST(NgAsciiUtilTest, upper_case)
{
  EXPECT_EQ(true, ng_ascii_util_is_lower_case('a'));
  EXPECT_EQ(true, ng_ascii_util_is_lower_case('m'));
  EXPECT_EQ(true, ng_ascii_util_is_lower_case('z'));
  
  EXPECT_EQ(false, ng_ascii_util_is_lower_case('A'));
  EXPECT_EQ(false, ng_ascii_util_is_lower_case('N'));
  EXPECT_EQ(false, ng_ascii_util_is_lower_case('Z'));
  EXPECT_EQ(false, ng_ascii_util_is_lower_case('1'));
  EXPECT_EQ(false, ng_ascii_util_is_lower_case(' '));
  EXPECT_EQ(false, ng_ascii_util_is_lower_case('\n'));
}


TEST(NgAsciUtilTest, letter)
{
  EXPECT_EQ(true, ng_ascii_util_is_letter('a'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('m'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('n'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('z'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('A'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('M'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('P'));
  EXPECT_EQ(true, ng_ascii_util_is_letter('W'));

  EXPECT_EQ(false, ng_ascii_util_is_letter(' '));
  EXPECT_EQ(false, ng_ascii_util_is_letter('\t'));
  EXPECT_EQ(false, ng_ascii_util_is_letter('1'));
  EXPECT_EQ(false, ng_ascii_util_is_letter('2'));
  EXPECT_EQ(false, ng_ascii_util_is_letter('+'));
  EXPECT_EQ(false, ng_ascii_util_is_letter('='));
}


TEST(NgAsciUtilTest, digit)
{
  EXPECT_EQ(true, ng_ascii_util_is_digit('1'));
  EXPECT_EQ(true, ng_ascii_util_is_digit('4'));
  EXPECT_EQ(true, ng_ascii_util_is_digit('5'));
  
  EXPECT_EQ(false, ng_ascii_util_is_digit('a'));
  EXPECT_EQ(false, ng_ascii_util_is_digit('b'));
  EXPECT_EQ(false, ng_ascii_util_is_digit('c'));
}


TEST(NgAsciUtilTest, id_char)
{
  EXPECT_EQ(true, ng_ascii_util_is_id('1'));
  EXPECT_EQ(true, ng_ascii_util_is_id('_'));
  EXPECT_EQ(true, ng_ascii_util_is_id('3'));
  EXPECT_EQ(true, ng_ascii_util_is_id('a'));
  EXPECT_EQ(true, ng_ascii_util_is_id('Z'));
  
  EXPECT_EQ(false, ng_ascii_util_is_id('/'));
  EXPECT_EQ(false, ng_ascii_util_is_id('+'));
  EXPECT_EQ(false, ng_ascii_util_is_id('-'));
  EXPECT_EQ(false, ng_ascii_util_is_id('*'));
}


TEST(NgAsciUtilTest, single_quote)
{
  EXPECT_EQ(true,  ng_ascii_util_is_single_quote('\''));
  EXPECT_EQ(false, ng_ascii_util_is_single_quote('"'));
  EXPECT_EQ(false, ng_ascii_util_is_single_quote(' '));
  EXPECT_EQ(false, ng_ascii_util_is_single_quote('1'));
  EXPECT_EQ(false, ng_ascii_util_is_single_quote('a'));
}


TEST(NgAsciUtilTest, double_quote)
{
  EXPECT_EQ(true,  ng_ascii_util_is_double_quote('"'));
  EXPECT_EQ(false, ng_ascii_util_is_double_quote('\''));
  EXPECT_EQ(false, ng_ascii_util_is_double_quote(' '));
  EXPECT_EQ(false, ng_ascii_util_is_double_quote('1'));
  EXPECT_EQ(false, ng_ascii_util_is_double_quote('a'));
}


TEST(NgAsciUtilTest, advance_char)
{
  // string to be tokenized
  const char* string = "A -> 'a'B";
  
  // set up begin/end iterators
  const char* curr = string;
  const char* end  = string + strlen(string);
  
  // preconditions:  curr at beginning of string,
  EXPECT_EQ(curr, string);
  // and end at end of string, i.e. greater than curr
  EXPECT_LT(curr, end);
  
  while(ng_ascii_util_advance_char(&curr, end)){
    // loop invariant: curr <= string <= end
    EXPECT_LE(string, curr);
    EXPECT_LE(curr, end);
  }
  
  // post-condition, curr == end
  EXPECT_EQ(curr, end);
}
