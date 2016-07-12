#include<stdio.h>
#include<test_fruit_int.h>



// test fruit which is just an int
void* test_fruit_int_cp_init(const void*src, void*tgt)
{
  *((int*)tgt) = *((int*)src);
  return tgt;
}


// de initializer for fruit which is inline c-string
void test_fruit_int_deinit(void* fruit)
{
  // shred just to know we've been here
  *((int*)fruit) = 0xdeadbeef;
}


bool test_fruit_int_equal(const void* fruit1,
			 const void* fruit2)
{
  return (*(int*)fruit1) == (*(int*)fruit2);
}


void test_fruit_int_dump(const void* fruit)
{
  printf("%d ", *((int*)fruit));
}


int test_fruit_int_compare(const void* f1, const void* f2)
{
  return *(int*)f1 - *(int*)f2;
}
