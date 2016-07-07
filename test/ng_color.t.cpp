#include <gtest/gtest.h>

#include <ng_color.h>
#include <string.h>



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

TEST(NgColorCompareTest, Comp)
{
  // test creation
  ng_color_t c0;
  ng_color_init(&c0, 1,2);
  
  ng_color_t c1;
  ng_color_init(&c1, 1,2);
  
  ng_color_t c3;
  ng_color_init(&c3, 2,1);
  
  ng_color_t c4;
  ng_color_init(&c4, 2,3);
  
  EXPECT_TRUE(ng_color_equal(&c0,&c1));
  EXPECT_TRUE(ng_color_equal(&c1,&c1));
  
  EXPECT_EQ(0, ng_color_compare(&c0,&c1));
  EXPECT_GT(0, ng_color_compare(&c1,&c3));
  EXPECT_LT(0, ng_color_compare(&c3,&c1));
  EXPECT_GT(0, ng_color_compare(&c3,&c4));
  EXPECT_LT(0, ng_color_compare(&c4,&c3));
  
  ng_color_deinit(&c0);
  ng_color_deinit(&c1);
  ng_color_deinit(&c3);
  ng_color_deinit(&c4);
}


