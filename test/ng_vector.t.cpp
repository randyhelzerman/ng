#include <gtest/gtest.h>

#include<ng_vector.h>
#include<ng_vector.t.h>

#include<stdbool.h>

#include<test_fruit_int.h>

const bool do_dump=true;


// Just test with basic integers types
TEST(NgVectorAllocTest, IntAllocEmptyDealloc)
{
  // Test initialization went ok
  ng_vector_t* v = ng_vector_new(sizeof(int), 10);
  EXPECT_NE((ng_vector_t*)0x0, v);
  EXPECT_EQ(10, v->max_);
  EXPECT_EQ(0,  v->numb_);
  
  // dump for fun
  if(do_dump){
    ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
    printf("\n");
  }
  
  // Test de-allocation, with null de_init
  ng_vector_delete(&v, sizeof(int), 0x0);
  EXPECT_EQ((ng_vector_t*)0x0, v);
  
  // allocate another one
  v = ng_vector_new(sizeof(int), 10);
  ng_vector_delete(&v, sizeof(int), test_fruit_int_deinit);
}


// insert a few integers, not enough to force realloc
TEST(NgVectorAllocTest, IntAllocSmallSizeDealloc)
{
  // test with bitcopy
  {
    ng_vector_t* v = ng_vector_new(sizeof(int), 10);
    EXPECT_EQ(true, ng_vector_empty(v));
    
    int tmp=5;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    
    EXPECT_EQ(false, ng_vector_empty(v));
    
    const int val = *((int*)ng_vector_back(v, sizeof(int)));
    EXPECT_EQ(7,val);
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }
    
    // Test de-allocation, with null de_init
    ng_vector_delete(&v, sizeof(int), 0x0);
    EXPECT_EQ((ng_vector_t*)0x0, v);
  }  
  
  // test with fruit_cp_init and fruit_de_init
  {
    ng_vector_t* v = ng_vector_new(sizeof(int), 10);
    
    int tmp=6;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), test_fruit_int_cp_init,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    
    const int val = *((int*)ng_vector_back(v, sizeof(int)));
    EXPECT_EQ(10,val);
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }
    
    // Test de-allocation, with null de_init
    ng_vector_delete(&v, sizeof(int), test_fruit_int_deinit);
    EXPECT_EQ((ng_vector_t*)0x0, v);
  }  
}



// insert a few integers, force realloc
TEST(NgVectorAllocTest, IntAllocMedSizeDealloc)
{
  // test with bitcopy
  {
    ng_vector_t* v = ng_vector_new(sizeof(int), 4);
    
    int tmp=5;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    EXPECT_EQ(3, v->numb_);
    EXPECT_EQ(4, v->max_);
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }
    
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    EXPECT_EQ(6, v->numb_);
    EXPECT_EQ(8, v->max_);
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }
    
    // Test de-allocation, with null de_init
    ng_vector_delete(&v, sizeof(int), 0x0);
    EXPECT_EQ((ng_vector_t*)0x0, v);
  }
  
  // test with fruit_cp_init and fruit_de_init
  {
    ng_vector_t* v = ng_vector_new(sizeof(int), 2);
    
    int tmp=6;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), test_fruit_int_cp_init,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    
    for(int i=0;i<v->numb_;i++){
      EXPECT_EQ(i+6, *(int*)ng_vector_at(v,i,sizeof(int)));
    }
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }

    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    
    for(int i=0;i<v->numb_;i++){
      EXPECT_EQ(i+6, *(int*)ng_vector_at(v,i,sizeof(int)));
    }
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }
    
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    ng_vector_push_back(&v, sizeof(int), (void*)(&tmp), 0,0);
    tmp++;
    
    for(int i=0;i<v->numb_;i++){
      EXPECT_EQ(i+6, *(int*)ng_vector_at(v,i,sizeof(int)));
    }
    
    // dump for fun
    if(do_dump){
      ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
      printf("\n");
    }
    
    // Test de-allocation, with null de_init
    ng_vector_delete(&v, sizeof(int), test_fruit_int_deinit);
    EXPECT_EQ((ng_vector_t*)0x0, v);
  }  
}

// insert a few integers, force realloc
TEST(NgVectorAllocTest, IntPushNPop)
{
  // test with bitcopy
  {
    ng_vector_t* v = ng_vector_new(sizeof(int), 4);
    
    for(int i=0;i<1000;i++){
      ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
    }
    
    for(int i=0;i<1000;i++){
      EXPECT_EQ(i, *(int*)ng_vector_at(v,i,sizeof(int)));
    }
    
    int test=1000;
    while(!ng_vector_empty(v)){
      test--;
      EXPECT_EQ(test, *(int*)ng_vector_back(v, sizeof(int)));
      ng_vector_pop_back(v, sizeof(int), 0x0);
    }
    
    EXPECT_EQ(0, v->numb_);

    // don't forget to clean up your memory
    ng_vector_delete(&v, sizeof(int), test_fruit_int_deinit);
    EXPECT_EQ((ng_vector_t*)0x0, v);
  }
}


// small binary search
TEST(NgVectorAllocTest, BinSearch)
{
  ng_vector_t* v = ng_vector_new(sizeof(int), 4);
  
  const int numb=99;
  
  for(int i=0;i<numb;i++){
    ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  }
  
  // test all possible combinations of l,h, and tgt
  // such that l <= tgt < numb < h
  for(int tgt=0;tgt<numb;tgt++){
    for(int l=0; l<=tgt; l++){
      for(int h=tgt+1; h<numb+1; h++){
	
	int answer
	  = ng_vector_binary_search_upper_bound(v, l,h,
						sizeof(int), (void*)&tgt,
						test_fruit_int_compare);
	EXPECT_EQ(tgt,answer);
      }
    }
  }
  
  ng_vector_delete(&v, sizeof(int), test_fruit_int_deinit);
}

    
// is it really a lower_bound???? Or is it an uppper bound?
TEST(NgVectorAllocTest, LowerBoundSearch)
{
  ng_vector_t* v = ng_vector_new(sizeof(int), 4);
  
  int i=1;
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  
  i=2;
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  
  i=3;
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  
  for(i=5;i<10;i++){
    ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
    ng_vector_push_back(&v, sizeof(int), (void*)(&i), 0,0);
  }
  
  printf("lower bound test vector:\n");
  ng_vector_dump(v, sizeof(int), test_fruit_int_dump);
  printf("\n");
  
  i = 3;
  int index
    = ng_vector_binary_search_lower_bound(v, 0,v->numb_,
					  sizeof(int), (void*)&i,
					  test_fruit_int_compare);
  printf("lower bound:  v[%d]=%d\n", index, *(int*)ng_vector_at(v, index, sizeof(int)));
  
  i = 3;
  index = ng_vector_binary_search_upper_bound(v, 0,v->numb_,
					      sizeof(int), (void*)&i,
					      test_fruit_int_compare);
  printf("upper bound:  v[%d]=%d\n", index, *(int*)ng_vector_at(v, index, sizeof(int)));
  
  ng_vector_delete(&v, sizeof(int), test_fruit_int_deinit);
}

    
