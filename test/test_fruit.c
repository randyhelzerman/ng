#include<test_fruit.h>

#include<stdio.h>
#include<string.h>

// This is a test fruit which is an inline-string on a rb-tree node.
// destructor for fruit which is inline c-string
void test_fruit_deinit(void* fruit)
{
  //  printf("freeing : %s\n", (char*)(fruit));
}

void test_fruit_dump(const void* fruit)
{
  //printf("%s", (char*)fruit);
}

int test_fruit_equal(const void* fruit1,
		     const void* fruit2)
{
  return !strcmp((const char*)fruit1, (const char*)fruit2);
}

void* test_fruit_cp_init(const void* src, void* tgt)
{
  strcpy((char*)tgt, (const char*)src);
  return tgt;
}

