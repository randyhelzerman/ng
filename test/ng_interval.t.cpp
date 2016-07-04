#include <gtest/gtest.h>

#include <ng_interval.h>
#include <string.h>


TEST(NgIntervalAllocTest, AllocShort)
{
  // test creation
  ng_interval_t* interval = 0x0;
  interval = ng_interval_eq_new("short",5);
  EXPECT_NE(interval,(ng_interval_t*)(0x0));

  // test that its initialized ok
  EXPECT_TRUE(!strcmp("short", ng_interval_word(interval)));
  EXPECT_EQ(interval->long_word_,         (char*)0x0);
  EXPECT_EQ(interval->max_next_states_,   5);
  EXPECT_EQ(interval->numb_next_states_,  0);
  
  // test deletion.  should zero out the pointer
  ng_interval_delete(&interval);
  EXPECT_EQ(interval,(ng_interval_t*)(0x0));
}

TEST(NgIntervalAllocTest, AllocLong)
{
  // test creation
  ng_interval_t* interval = 0x0;
  interval = ng_interval_eq_new("supercalifragilisticexpialadotious",5);
  EXPECT_NE(interval,(ng_interval_t*)(0x0));
  
  // test that its initialized ok
  EXPECT_TRUE(!strcmp("supercalifragilisticexpialadotious", 
		      ng_interval_word(interval)));
  EXPECT_NE(interval->long_word_,         (char*)0x0);
  EXPECT_EQ(interval->max_next_states_,   5);
  EXPECT_EQ(interval->numb_next_states_,  0);
  
  // test deletion.  should zero out the pointer
  ng_interval_delete(&interval);
  EXPECT_EQ(interval,(ng_interval_t*)(0x0));
}
