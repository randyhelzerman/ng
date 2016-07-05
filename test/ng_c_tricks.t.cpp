#include <gtest/gtest.h>


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
  printf("small size = %lu\n", small_size);
  printf("large size = %lu\n", large_size);

  EXPECT_EQ(small_size,large_size);
}
