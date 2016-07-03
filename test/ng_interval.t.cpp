#include <gtest/gtest.h>

#include <ng_interval.h>
#include <string.h>


TEST(NoopTest, NoopTest)
{
  EXPECT_EQ(1,1);
}


TEST(NgAllocTest, Alloc)
{
  ng_interval_t* interval = 0x0;
  interval = ng_interval_new("short",5);
  
  EXPECT_NE(interval,(ng_interval_t*)(0x0));

  EXPECT_TRUE(!strcmp("short", ng_interval_word(interval)));
  
  EXPECT_EQ(1,1);
}


