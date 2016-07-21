#include <gtest/gtest.h>

#include <stdbool.h>
#include <ng_interval.h>
#include <ng_interval.t.h>
#include <string.h>

static const bool do_print = false;


TEST(NgIntervalAllocTest, AllocShort)
{
  // test creation
  ng_interval_t* interval = 0x0;
  interval = ng_interval_eq_new("short");
  EXPECT_NE(interval,(ng_interval_t*)(0x0));
  
  // test that its initialized ok
  EXPECT_TRUE(!strcmp("short", ng_interval_word(interval)));
  EXPECT_EQ(interval->numb_next_states_,  0);
  
  // test deletion.  should zero out the pointer
  ng_interval_delete(&interval);
  EXPECT_EQ(interval,(ng_interval_t*)(0x0));
}


TEST(NgIntervalAllocTest, AllocLong)
{
  // create two intervals to represent the
  // range 0=9 inclusive
  ng_interval_t* int1=ng_interval_eq_new("0");
  ng_interval_t* int2=ng_interval_gt_new("9");
  
  // Test an interval below the range
  ng_interval_t* int0=ng_interval_eq_new("/");
  const int cmp1 = ng_interval_compare(int0, int1);
  EXPECT_LT(cmp1,0);
  
  // Test an interval above the range
  ng_interval_t* int4=ng_interval_eq_new(">");
  const int cmp2 = ng_interval_compare(int1, int4);
  EXPECT_LT(cmp2,0);
  
  // Test an equal one
  ng_interval_t* int5=ng_interval_eq_new("0");
  const int cmp3 = ng_interval_compare(int1, int5);
  EXPECT_EQ(0, cmp3);
  
  // test creation
  ng_interval_t* interval = 0x0;
  interval = ng_interval_eq_new("supercalifragilisticexpialadotious");
  EXPECT_NE(interval,(ng_interval_t*)(0x0));
  
  // test that its initialized ok
  EXPECT_TRUE(!strncmp("supercalifragilisticexpialadotious", 
		       ng_interval_word(interval),15));
  EXPECT_EQ(interval->numb_next_states_,  0);
  
  // test deletion.  should zero out the pointer
  ng_interval_delete(&interval);
  EXPECT_EQ(interval,(ng_interval_t*)(0x0));

  ng_interval_delete(&int0);
  ng_interval_delete(&int1);
  ng_interval_delete(&int2);
  ng_interval_delete(&int4);
  ng_interval_delete(&int5);
}


TEST(NgIntervalAccessTest, Equality)
{
  // create two intervals to represent the
  // range 0=9 inclusive
  ng_interval_t* int1=ng_interval_eq_new("0");
  ng_interval_t* int2=ng_interval_eq_new("9");
  ng_interval_t* int3=ng_interval_eq_new("0");
  
  if(do_print) ng_interval_dump(int1);
  if(do_print) printf("\n");
  if(do_print) ng_interval_dump(int3);
  if(do_print) printf("\n");
  EXPECT_TRUE(ng_interval_equal(int1,int3));
  if(do_print) printf("\n");
  
  if(do_print) ng_interval_dump(int2);
  if(do_print) printf("\n");
  if(do_print) ng_interval_dump(int3);
  if(do_print) printf("\n");
  EXPECT_FALSE(ng_interval_equal(int2,int3));
  if(do_print) printf("\n");
  
  // now push some stuffs
  ng_interval_push_color(int1, 1,2);
  ng_interval_push_color(int2, 1,2);
  ng_interval_push_color(int3, 1,2);
  
  if(do_print) ng_interval_dump(int1);
  if(do_print) printf("\n");
  if(do_print) ng_interval_dump(int3);
  if(do_print) printf("\n");
  EXPECT_TRUE(ng_interval_equal(int1,int3));
  if(do_print) printf("\n");
  
  if(do_print) ng_interval_dump(int2);
  if(do_print) printf("\n");
  if(do_print) ng_interval_dump(int3);
  if(do_print) printf("\n");
  EXPECT_FALSE(ng_interval_equal(int2,int3));
  
  // now push more stuffs
  ng_interval_push_color(int3, 3,4);
  if(do_print) ng_interval_dump(int1);
  if(do_print) printf("\n");
  if(do_print) ng_interval_dump(int3);
  if(do_print) printf("\n");
  EXPECT_FALSE(ng_interval_equal(int1,int3));
  
  ng_interval_delete(&int1);
  ng_interval_delete(&int2);
  ng_interval_delete(&int3);
}
