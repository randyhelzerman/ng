#include <gtest/gtest.h>

#include <ng_rb_tree_node.h>
#include <ng_interval.h>
#include <string.h>

#include<test_fruit.h>


TEST(NgRBAllocTest, Alloc)
{
  // this is going to be a node containing an ng_interval_t, so make
  // one for it to hold.
  ng_interval_t* interval = 0x0;
  interval = ng_interval_eq_new("short");
  EXPECT_NE(interval,(ng_interval_t*)(0x0));
  
  // test creation
  ng_rb_tree_node_t* node = 0x0;
  node = ng_rb_tree_node_new((ng_rb_tree_node_t*)2,
			     (ng_rb_tree_node_t*)3,
			     
			     sizeof(ng_interval_t),
			     (void*)interval,
			     (void*(*)(const void*,
				       void*))ng_interval_cp_init);
  EXPECT_NE(node,(ng_rb_tree_node_t*)(0x0));
  
  // test dumpage...not really a test; have to verify on the screen...
  ng_rb_tree_node_dump(node, (void(*)(const void*))ng_interval_dump);
  
  // test that its initialized ok
  EXPECT_EQ(node->kids_[0], (ng_rb_tree_node_t*)2);
  EXPECT_EQ(node->kids_[1], (ng_rb_tree_node_t*)3);
  EXPECT_EQ(true,ng_interval_equal((ng_interval_t*)&node->fruit_, interval));
  
  // test deletion.  should zero out the pointer
  ng_rb_tree_node_delete(&node, (void(*)(void*))ng_interval_uninit);
  EXPECT_EQ(node,(ng_rb_tree_node_t*)(0x0));

  ng_interval_delete(&interval);
}


// tests some of the debugging facilities; structural
// equivalecne, validity of rb tree, etc.
TEST(NgRBDebugTest, Debug)
{
  // Test to see that null node is correct and has height 1
  EXPECT_EQ(1, ng_rb_tree_node_correct(0x0));
  
  // Test to see that single black node has height 2
  ng_rb_tree_node_t* Q = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"Q",test_fruit_cp_init);
  
  Q->red_ = false;
  EXPECT_EQ(2, ng_rb_tree_node_correct(Q));
  
  // Test to see that single red node has height 1
  ng_rb_tree_node_t* P = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"P",test_fruit_cp_init);
  P->red_ = true;
  EXPECT_EQ(1, ng_rb_tree_node_correct(P));
  
  // Test detection of consecutive red node -- left side
  ng_rb_tree_node_t* A = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"A",test_fruit_cp_init);
  A->red_ = true;
  P->kids_[0]  = A;
  EXPECT_EQ(0, ng_rb_tree_node_correct(P));

  // Test detection of consecutive red node -- right side
  ng_rb_tree_node_t* B = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"B",test_fruit_cp_init);
  B->red_ = true;
  P->kids_[0]  = 0x0;
  P->kids_[1]  = B;
  EXPECT_EQ(0, ng_rb_tree_node_correct(P));
  
  // Test detection of consecutive red node -- both sides
  P->kids_[0]  = A;
  EXPECT_EQ(0, ng_rb_tree_node_correct(P));
  
  // Test black height mismatch
  ng_rb_tree_node_t* C = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"C",test_fruit_cp_init);
  
  Q->kids_[0]  = P;   Q->red_ = false;  P->red_ = false;
  Q->kids_[1]  = C;   C->red_ = false;
  P->kids_[0]  = A;   A->red_ = false;
  P->kids_[1]  = B;   B->red_ = false;
  
  EXPECT_EQ(0, ng_rb_tree_node_correct(Q));
  
  // Test for correct black-height calculation on valid tree
  Q->red_ = false;
  P->red_ = true;
  A->red_ = false;
  B->red_ = false;
  C->red_ = false;
  
  EXPECT_EQ(3, ng_rb_tree_node_correct(Q));
  
  // delete everything created in this function
  ng_rb_tree_node_delete(&Q, test_fruit_deinit);
  ng_rb_tree_node_delete(&P, test_fruit_deinit);
  ng_rb_tree_node_delete(&A, test_fruit_deinit);
  ng_rb_tree_node_delete(&B, test_fruit_deinit);
  ng_rb_tree_node_delete(&C, test_fruit_deinit);
}


// test to see if the ng_rb_tree_node_is_red() function
// works correctly.
TEST(NgRBAccessTest, IsRed)
{
  // A null node is colored black
  ng_rb_tree_node_t* node = 0x0;
  EXPECT_FALSE(ng_rb_tree_node_is_red(node));

  // when created, by default, a node is black
  node = ng_rb_tree_node_new(0x0, 0x0,
			     5,(void*)"node",test_fruit_cp_init);
  EXPECT_FALSE(ng_rb_tree_node_is_red(node));

  // when a node's red member is set to true, its red 
  node->red_ = true;
  EXPECT_TRUE(ng_rb_tree_node_is_red(node));
  
  // when we set it back to false, it is black
  node->red_ = false;
  EXPECT_FALSE(ng_rb_tree_node_is_red(node));
  
  // free up memory.
  ng_rb_tree_node_delete(&node, test_fruit_deinit);
}
