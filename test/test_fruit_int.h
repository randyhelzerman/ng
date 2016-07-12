#ifndef TEST_FRUIT_INT__H
#define TEST_FRUIT_INT__H

#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

  // test fruit which is just an int
  void* test_fruit_int_cp_init(const void*src, void*tgt);
  
  // de initializer for fruit which is inline c-string
  void test_fruit_int_deinit(void* fruit);
  
  void test_fruit_int_dump(const void* fruit);
  
  bool test_fruit_int_equal(const void* fruit1,
			    const void* fruit2);

  void test_fruit_int_dump(const void* fruit);

  int test_fruit_int_compare(const void*, const void*);

#ifdef __cplusplus
};
#endif



#endif  // test fruit int include file guard
