#include <gtest/gtest.h>

#include <ng_rb_tree_node.h>
#include <ng_interval.h>
#include <string.h>


TEST(NgRBAllocTest, Alloc)
{
  // this is going to be a node containing an ng_interval_t, so make
  // one for it to hold.
  ng_interval_t* interval = 0x0;
  interval = ng_interval_eq_new("short",5);
  EXPECT_NE(interval,(ng_interval_t*)(0x0));
  
  // test creation
  ng_rb_tree_node_t* node = 0x0;
  node = ng_rb_tree_node_new((ng_rb_tree_node_t*)2,
			     (ng_rb_tree_node_t*)3,
			     (void*)interval);
  EXPECT_NE(node,(ng_rb_tree_node_t*)(0x0));
  
  // test dumpage...not really a test; have to verify on the screen...
  ng_rb_tree_node_dump(node, (void(*)(const void*))ng_interval_dump);
  
  // test that its initialized ok
  EXPECT_EQ(node->parent_, (ng_rb_tree_node_t*)1);
  EXPECT_EQ(node->kid_[0], (ng_rb_tree_node_t*)2);
  EXPECT_EQ(node->kid_[1], (ng_rb_tree_node_t*)3);
  EXPECT_EQ(node->fruit_,  (void*)interval);
  
  // test deletion.  should zero out the pointer
  ng_rb_tree_node_delete(&node, (void(*)(void**))ng_interval_delete);
  EXPECT_EQ(node,(ng_rb_tree_node_t*)(0x0));
}

