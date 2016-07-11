#ifndef TEST_FRUIT__H
#define TEST_FRUIT__H

#ifdef __cplusplus
extern "C" {
#endif


  // This is a test fruit which is an inline-string on a rb-tree node.

  // no constructors/destructors needed, because its inline so we
  // will let the rb tree do the memory managment
  
  // we do need cp initializers and de initializer tho.
  void* test_fruit_cp_init(const void* src, void* tgt);
  
  // de initializer for fruit which is inline c-string
  void test_fruit_deinit(void* fruit);
  
  void test_fruit_dump(const void* fruit);
  
  int test_fruit_equal(const void* fruit1,
		       const void* fruit2);


#ifdef __cplusplus
};
#endif



#endif  // test fruit include file guard
