#include <gtest/gtest.h>

#include <ng_color.h>
#include <string.h>


TEST(NoopTest, NoopTest)
{
  EXPECT_EQ(1,1);
}


TEST(NgColorAllocTest, Alloc)
{
  // test creation
  ng_color_t* color = 0x0;
  color = ng_color_new(5,6);
  EXPECT_NE(color,(ng_color_t*)(0x0));
  
  // test that its initialized ok
  EXPECT_EQ(color->state_, 5);
  EXPECT_EQ(color->delta_, 6);

  // test deletion.  should zero out the pointer
  ng_color_delete(&color);
  EXPECT_EQ(color,(ng_color_t*)(0x0));
}


