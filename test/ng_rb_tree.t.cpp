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
  EXPECT_EQ(tree->root_,  (ng_rb_tree_node_t*)0x0);
  EXPECT_EQ(tree->count_, 0);
  
  // test deletion.  should zero out the pointer
  ng_rb_tree_delete(&tree, 0x0);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
}


// This tests creation/deletion of a tree with some
// hand-inserted nodes in it.

int numb_deletions = 0; // keep track of the number of node deletions.

// destructor for fruit which is just a c-string.
void fruit_deinit(void* fruit)
{
  numb_deletions++;
  printf("freeing : %s\n", (char*)(fruit));
}

void fruit_dump(const void* fruit)
{
  printf("%s", (char*)fruit);
}

int fruit_equal(const void* fruit1,
		const void* fruit2)
{
  return !strcmp((const char*)fruit1, (const char*)fruit2);
}

void* fruit_cp_init(const void* src, void* tgt)
{
  strcpy((char*)tgt, (const char*)src);
  return tgt;
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
  ng_rb_tree_node_t* A = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* Q = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"Q",fruit_cp_init);
  ng_rb_tree_node_t* P = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"P",fruit_cp_init);
  
  tree->root_  = Q;
  Q->kids_[0]  = P;
  Q->kids_[1]  = C; 
  P->kids_[0]  = A; 
  P->kids_[1]  = B;
  
  // print tree out for fun
  ng_rb_tree_dump(tree,fruit_dump);
  
  // test deletion.  should zero out the pointer
  numb_deletions = 0;
  ng_rb_tree_delete(&tree, fruit_deinit);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
  
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
}


// Test right rotation of node
TEST(NgRBTRotateTest, RotRight)
{
  // now create some equivalent nodes
  ng_rb_tree_node_t* A1 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B1 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C1 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* Q1 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"Q",fruit_cp_init);
  ng_rb_tree_node_t* P1 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"P",fruit_cp_init);
  
  ng_rb_tree_node_t* A2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* Q2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"Q",fruit_cp_init);
  ng_rb_tree_node_t* P2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"P",fruit_cp_init);
  
  
  // create left tree
  ng_rb_tree_t* left_tree = ng_rb_tree_new();
  left_tree->root_ = Q1;;
  Q1->kids_[0]     = P1;
  Q1->kids_[1]     = C1;
  P1->kids_[0]     = A1;
  P1->kids_[1]     = B1;
  
  // create right tree
  ng_rb_tree_t* right_tree = ng_rb_tree_new();
  right_tree->root_ = P2;
  P2->kids_[0]  = A2;
  P2->kids_[1]  = Q2;
  Q2->kids_[0]  = B2;
  Q2->kids_[1]  = C2;
	    
  // before rotation, they should not be structurally
  // equivalent
  EXPECT_FALSE(ng_rb_tree_structurally_equivalent(left_tree,
						  right_tree,
						  fruit_equal));
	    
	    // rotate right!!
  left_tree->root_ = ng_rb_tree_rotate_(Q1,1);
  
  // print tree out for fun
  printf("after rotation\n");
  ng_rb_tree_dump(left_tree,fruit_dump);
  
  // print tree out for fun
  printf("right tree\n");
  ng_rb_tree_dump(right_tree,fruit_dump);
  
  // after rotation, P1 should be the root
  EXPECT_EQ(P1, left_tree->root_);
  
  // after rotation, left should be strutrually
  // equivalent to right.
  EXPECT_TRUE(ng_rb_tree_structurally_equivalent(left_tree,
						 right_tree,
						 fruit_equal));
  
  // test deletion.  should zero out the pointer
  numb_deletions = 0;
  ng_rb_tree_delete(&left_tree, fruit_deinit);
  EXPECT_EQ(left_tree,(ng_rb_tree_t*)(0x0));
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
  
  // delete right tree
  numb_deletions = 0;
  ng_rb_tree_delete(&right_tree, fruit_deinit);
  EXPECT_EQ(left_tree,(ng_rb_tree_t*)(0x0));
  EXPECT_EQ(numb_deletions, 5);
}


// Test left rotation of node
TEST(NgRBTRotateTest, RotLeft)
{
  // now create some equivalent nodes
  // now create some equivalent nodes
  ng_rb_tree_node_t* A1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* Q1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"Q",fruit_cp_init);
  ng_rb_tree_node_t* P1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"P",fruit_cp_init);
  
  ng_rb_tree_node_t* A2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* Q2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"Q",fruit_cp_init);
  ng_rb_tree_node_t* P2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"P",fruit_cp_init);
  
  // create left tree
  ng_rb_tree_t* left_tree = ng_rb_tree_new();
  left_tree->root_   = Q1;
  Q1->kids_[0]       = P1;
  Q1->kids_[1]       = C1;
  P1->kids_[0]       = A1;
  P1->kids_[1]       = B1;
  
  // create right tree
  ng_rb_tree_t* right_tree = ng_rb_tree_new();
  right_tree->root_  = P2;
  P2->kids_[0]       = A2;
  P2->kids_[1]       = Q2;
  Q2->kids_[0]       = B2;
  Q2->kids_[1]       = C2;
  
  // before rotation, they should not be structurally
  // equivalent
  EXPECT_FALSE(ng_rb_tree_structurally_equivalent(left_tree,
						  right_tree,
						  fruit_equal));
  
  // rotate left!!
  right_tree->root_ = ng_rb_tree_rotate_(P2,0);
  
  // print tree out for fun
  printf("after rotation\n");
  ng_rb_tree_dump(right_tree,fruit_dump);
  
  // print tree out for fun
  printf("left tree\n");
  ng_rb_tree_dump(left_tree,fruit_dump);
  
  // after rotation, Q2 should be the root
  EXPECT_EQ(Q2, right_tree->root_);
  
  // after rotation, left should be strutrually
  // equivalent to right.
  EXPECT_TRUE(ng_rb_tree_structurally_equivalent(left_tree,
						 right_tree,
						 fruit_equal));
  
  // test deletion.  should zero out the pointer
  numb_deletions = 0;
  ng_rb_tree_delete(&left_tree, fruit_deinit);
  EXPECT_EQ(left_tree,(ng_rb_tree_t*)(0x0));
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
  
  // delete right tree--no fruit deletion
  numb_deletions = 0;
  ng_rb_tree_delete(&right_tree, fruit_deinit);
  EXPECT_EQ(left_tree,(ng_rb_tree_t*)(0x0));
  EXPECT_EQ(numb_deletions, 5);
}


