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
  EXPECT_EQ(tree->root_,   (ng_rb_tree_node_t*)0x0);
  EXPECT_EQ(tree->count_,  0);
  
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
  numb_deletions = 0;
  ng_rb_tree_delete(&tree, fruit_delete);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
  
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
}


TEST(NgRBTRotateTest, RotRight)
{
  // now create some equivalent nodes
  ng_rb_tree_node_t* A1 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("A"));
  ng_rb_tree_node_t* B1 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("B"));
  ng_rb_tree_node_t* C1 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("C"));
  ng_rb_tree_node_t* Q1 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("Q"));
  ng_rb_tree_node_t* P1 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("P"));
  
  ng_rb_tree_node_t* A2 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("A"));
  ng_rb_tree_node_t* B2 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("B"));
  ng_rb_tree_node_t* C2 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("C"));
  ng_rb_tree_node_t* Q2 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("Q"));
  ng_rb_tree_node_t* P2 = ng_rb_tree_node_new(0x0, 0x0, 0x0, strdup("P"));
  
  // create left tree
  ng_rb_tree_t* left_tree = ng_rb_tree_new();
  left_tree->root_ = Q1;    Q1->parent_ = 0x0;
  Q1->left_        = P1;    P1->parent_ = Q1;
  Q1->right_       = C1;    C1->parent_ = Q1;
  P1->left_        = A1;    A1->parent_ = P1;
  P1->right_       = B1;    B1->parent_ = P1;
  
  // print tree out for fun
  ng_rb_tree_dump(left_tree,fruit_dump);
  
  // create right tree
  ng_rb_tree_t* right_tree = ng_rb_tree_new();
  right_tree->root_ = P2;   P2->parent_ = 0x0;
  P2->left_  = A2;           A2->parent_ = P2;
  P2->right_ = Q2;           Q2->parent_ = P2;
  Q2->left_ =  B2;           B2->parent_ = Q2;
  Q2->right_ = C2;           C2->parent_ = Q2;
  
  // print tree out for fun
  ng_rb_tree_dump(right_tree,fruit_dump);
  
  // rotate right!!
  ng_rb_tree_rotate_node_right(&left_tree->root_);
  
  // after rotation, P1 should be the root
  EXPECT_EQ(P1, left_tree->root_);
  
  // after rotation, left should be strutrually
  // equivalent to right.
  
  // test deletion.  should zero out the pointer
  numb_deletions = 0;
  ng_rb_tree_delete(&tree, fruit_delete);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
  
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
}


