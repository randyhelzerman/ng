#include <gtest/gtest.h>

#include <stdbool.h>

const bool do_print = false;

// this is to test if your struct hack is going to work

typedef struct ctricks_small{
  int i;
  float j;
} ctricks_small_t;

typedef struct ctricks_large{
  int i;
  float j;
  char fruit[];
} ctricks_large_t;

TEST(CTricks, structSize)
{
  const size_t small_size = sizeof(ctricks_small_t);
  const size_t large_size = sizeof(ctricks_large_t);
  if(do_print) printf("small size = %lu\n", small_size);
  if(do_print) printf("large size = %lu\n", large_size);

  EXPECT_EQ(small_size,large_size);
}


// Tests whether ! always returns a 1 or a zero
TEST(CTricks, boolification)
{
  // easy cases
  int i = 1;
  EXPECT_EQ(false, !i);
  EXPECT_EQ(true, !!i);
  
  i=0;
  EXPECT_EQ(true, !i);
  EXPECT_EQ(false, !!i);
  
  // wierder cases
  i = 0xdeadbeef;
  EXPECT_EQ(false, !i);
  EXPECT_EQ(true, !!i);

  i = 5;
  EXPECT_EQ(false, !i);
  EXPECT_EQ(true, !!i);
}
