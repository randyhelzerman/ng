#include <gtest/gtest.h>

#include <ng_rb_tree.h>


// test creation/destruction of an empty rb tree.

TEST(NgRBTAllocTest, Alloc0)
{
  // test creation
  ng_rb_tree_t* tree = 0x0;
  tree = ng_rb_tree_new();
  EXPECT_NE(tree,(ng_rb_tree_t*)(0x0));
  
  // test that its initialized ok
  EXPECT_EQ(tree->root_,     (ng_rb_tree_node_t*)0x0);
  EXPECT_EQ(tree->count_,    0);
  
  // test deletion.  should zero out the pointer
  ng_rb_tree_delete(&tree, 0x0);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
}


// This tests creation/deletion of a tree with some
// hand-inserted nodes in it.

int numb_deletions = 0; // keep track of the number of node deletions.

// destructor for fruit which is just a c-string.
void fruit_delete(void** fruit)
{
  numb_deletions++;
  printf("freeing : %s\n", (char*)(*fruit));
  free(*fruit);
  *fruit = 0x0;
}

void fruit_dump(const void* fruit)
{
  printf("%s", (char*)fruit);
}

TEST(NgRBTAllocTest, Alloc1)
{
  // test creation
  ng_rb_tree_t* tree = 0x0;
  tree = ng_rb_tree_new();
  EXPECT_NE(tree,(ng_rb_tree_t*)(0x0));
  
  // test that its initialized ok
  EXPECT_EQ(tree->root_,     (ng_rb_tree_node_t*)0x0);
  EXPECT_EQ(tree->count_,    0);
  
  // now create some nodes to put in there for it.
  ng_rb_tree_node_t* A = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("A"));
  ng_rb_tree_node_t* B = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("B"));
  ng_rb_tree_node_t* C = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("C"));
  ng_rb_tree_node_t* Q = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("Q"));
  ng_rb_tree_node_t* P = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("P"));

  tree->root_ = Q;
  Q->left_  = P;   P->parent_ = Q;
  Q->right_ = C;   C->parent_ = Q;
  P->left_  = A;   A->parent_ = P;
  P->right_ = B;   B->parent_ = P;
  
  // print tree out for fun
  ng_rb_tree_dump(tree,fruit_dump);
  
  // test deletion.  should zero out the pointer
  ng_rb_tree_delete(&tree, fruit_delete);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
  
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
}


