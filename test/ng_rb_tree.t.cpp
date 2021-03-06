#include <gtest/gtest.h>

#include <stdbool.h>
#include <ng_rb_tree.h>
#include <ng_rb_tree.t.h>

#include <ng_rb_tree_node.h>
#include <ng_rb_tree_node.t.h>

#include <math.h>

const bool do_print = false;

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
  // printf("freeing : %s\n", (char*)(fruit));
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

int fruit_compare(const void* src, const void* tgt)
{
  return strcmp((char*)src,(char*)tgt);
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
  if(do_print)  ng_rb_tree_dump(tree,fruit_dump);
  
  // test deletion.  should zero out the pointer
  numb_deletions = 0;
  ng_rb_tree_delete(&tree, fruit_deinit);
  EXPECT_EQ(tree,(ng_rb_tree_t*)(0x0));
  
  // all 5 nodes should have been deleted
  EXPECT_EQ(numb_deletions, 5);
}


// rotate node     Returns 1 if successful.
//
//       Q                  P
//      / \   dir=1 ===>   / \
//     p   C              A   q
//    / \                    / \
//   A   B                  B   C



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
  
  // create left tree
  ng_rb_tree_t* left_tree = ng_rb_tree_new();
  left_tree->root_ = Q1;;
  Q1->kids_[0]     = P1;
  Q1->kids_[1]     = C1;
  P1->kids_[0]     = A1;
  P1->kids_[1]     = B1;

  P1->red_ = true;
  
  // create right tree
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
  
  
  ng_rb_tree_t* right_tree = ng_rb_tree_new();
  right_tree->root_ = P2;
  P2->kids_[0]  = A2;
  P2->kids_[1]  = Q2;
  Q2->kids_[0]  = B2;
  Q2->kids_[1]  = C2;

  Q2->red_ = true;
	    
  // before rotation, they should not be structurally
  // equivalent
  EXPECT_FALSE(ng_rb_tree_structurally_equivalent(left_tree,
						  right_tree,
						  fruit_equal));
	    
  // rotate right!!
  left_tree->root_ = ng_rb_tree_rotate_(Q1,1);
  
  // print tree out for fun
  if (do_print) printf("after rotation\n");
  if (do_print) ng_rb_tree_dump(left_tree,fruit_dump);
  
  // print tree out for fun
  if (do_print) printf("right tree\n");
  if (do_print) ng_rb_tree_dump(right_tree,fruit_dump);
  
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


// rotate node     Returns 1 if successful.
//
//       Q    <=== dir=0    P
//      / \                / \
//     p   C              A   q
//    / \                    / \
//   A   B                  B   C


// Test left rotation of node
TEST(NgRBTRotateTest, RotLeft)
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
  
  // create left tree
  ng_rb_tree_t* left_tree = ng_rb_tree_new();
  left_tree->root_   = Q1;
  Q1->kids_[0]       = P1;
  Q1->kids_[1]       = C1;
  P1->kids_[0]       = A1;
  P1->kids_[1]       = B1;

  P1->red_ = true;
  
  // create right tree
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
  
  ng_rb_tree_t* right_tree = ng_rb_tree_new();
  right_tree->root_  = P2;
  P2->kids_[0]       = A2;
  P2->kids_[1]       = Q2;
  Q2->kids_[0]       = B2;
  Q2->kids_[1]       = C2;
  
  Q2->red_ = true;

  if(do_print) printf("\nright tree:\n");
  if(do_print) ng_rb_tree_dump(right_tree,fruit_dump);
  
  if(do_print) printf("\nleft tree:\n");
  if(do_print) ng_rb_tree_dump(left_tree,fruit_dump);
  
  // before rotation, they should not be structurally
  // equivalent
  EXPECT_FALSE(ng_rb_tree_structurally_equivalent(left_tree,
						  right_tree,
						  fruit_equal));
  
  // rotate left!!
  right_tree->root_ = ng_rb_tree_rotate_(P2,0);
  
  // print tree out for fun
  if (do_print) printf("after rotation\n");
  // print tree out for fun
  if (do_print) printf("right tree\n");
  if(do_print) ng_rb_tree_dump(right_tree,fruit_dump);
  
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


// rotate node     Returns 1 if successful.
// 
//        D                    D                    C
//       /  \    dir=1 ===>   /  \       ==>      /   \
//     B     E               C     E             b     d
//    / \    | \            / \    | \         / |    /  \
//   A   c   5  6          b   4   5  6       A  3   4    E
//  / |  | \              / \               / |          /  \
// 1  2  3  4            A   3             1  2          5    6
//                     / |    
//                    1  2    
//                


// Test right double rotation of node
TEST(NgRBTRotateTest, RotRightDouble)
{
  // now create some equivalent nodes
  ng_rb_tree_node_t* A1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* D1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"D",fruit_cp_init);
  ng_rb_tree_node_t* E1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"E",fruit_cp_init);
  
  ng_rb_tree_node_t* n1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"1",fruit_cp_init);
  
  ng_rb_tree_node_t* n2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"2",fruit_cp_init);
  
  ng_rb_tree_node_t* n3 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"3",fruit_cp_init);
  
  ng_rb_tree_node_t* n4 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"4",fruit_cp_init);
  
  ng_rb_tree_node_t* n5 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"5",fruit_cp_init);
  
  ng_rb_tree_node_t* n6 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"6",fruit_cp_init);
  
  
  // create left tree
  ng_rb_tree_t tree1;
  tree1.root_ = D1;
  D1->kids_[0]     = B1;
  D1->kids_[1]     = E1;
  
  B1->kids_[0]     = A1;
  B1->kids_[1]     = C1;

  A1->kids_[0]     = n1;
  A1->kids_[1]     = n2;
  
  C1->kids_[0]     = n3;
  C1->kids_[1]     = n4;

  E1->kids_[0]     = n5;
  E1->kids_[1]     = n6;

  if(do_print) printf("before rotation: tree1=\n");
  if(do_print) ng_rb_tree_dump(&tree1,fruit_dump);
  
  // create right tree
  ng_rb_tree_node_t* A2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* D2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"D",fruit_cp_init);
  ng_rb_tree_node_t* E2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"E",fruit_cp_init);
  
  ng_rb_tree_node_t* m1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"1",fruit_cp_init);
  
  ng_rb_tree_node_t* m2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"2",fruit_cp_init);
  
  ng_rb_tree_node_t* m3 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"3",fruit_cp_init);
  
  ng_rb_tree_node_t* m4 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"4",fruit_cp_init);
  
  ng_rb_tree_node_t* m5 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"5",fruit_cp_init);
  
  ng_rb_tree_node_t* m6 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"6",fruit_cp_init);
  ng_rb_tree_t tree2;
  tree2.root_   =  C2;
  C2->kids_[0]  =  B2;
  C2->kids_[1]  =  D2;
  
  B2->kids_[0]  =  A2;
  B2->kids_[1]  =  m3;

  A2->kids_[0]  =  m1;
  A2->kids_[1]  =  m2;
  
  D2->kids_[0]  =  m4;
  D2->kids_[1]  =  E2;
  
  E2->kids_[0]  =  m5;
  E2->kids_[1]  =  m6;

  B2->red_ = true;
  D2->red_ = true;

  // print tree out for fun
  if(do_print) printf("\ntree2\n");
  if(do_print) ng_rb_tree_dump(&tree2,fruit_dump);
  
  // before rotation, they should not be structurally
  // equivalent
  EXPECT_FALSE(ng_rb_tree_node_structurally_equivalent(D1,
						       C2,
						       fruit_equal));
  
  // double rotate right!!
  tree1.root_ = ng_rb_tree_rotate_double_(D1,1);
  
  // print tree out for fun
  if(do_print) printf("after rotation\n");
  if(do_print) ng_rb_tree_dump(&tree1,fruit_dump);
  
  // after rotation, left should be strutrually
  // equivalent to right.
  EXPECT_TRUE(ng_rb_tree_structurally_equivalent(&tree1,
						 &tree2,
						 fruit_equal));

  // Root node should be black
  EXPECT_FALSE(tree1.root_->red_);
  // its kids should be red
  EXPECT_TRUE(tree1.root_->kids_[0]->red_);
  EXPECT_TRUE(tree1.root_->kids_[1]->red_);
  
  ng_rb_tree_node_delete(&A1, fruit_deinit);
  ng_rb_tree_node_delete(&B1, fruit_deinit);
  ng_rb_tree_node_delete(&C1, fruit_deinit);
  ng_rb_tree_node_delete(&D1, fruit_deinit);
  ng_rb_tree_node_delete(&E1, fruit_deinit);
  
  ng_rb_tree_node_delete(&A2, fruit_deinit);
  ng_rb_tree_node_delete(&B2, fruit_deinit);
  ng_rb_tree_node_delete(&C2, fruit_deinit);
  ng_rb_tree_node_delete(&D2, fruit_deinit);
  ng_rb_tree_node_delete(&E2, fruit_deinit);
  
  ng_rb_tree_node_delete(&n1, fruit_deinit);
  ng_rb_tree_node_delete(&n2, fruit_deinit);
  ng_rb_tree_node_delete(&n3, fruit_deinit);
  ng_rb_tree_node_delete(&n4, fruit_deinit);
  ng_rb_tree_node_delete(&n5, fruit_deinit);
  ng_rb_tree_node_delete(&n6, fruit_deinit);
  
  ng_rb_tree_node_delete(&m1, fruit_deinit);
  ng_rb_tree_node_delete(&m2, fruit_deinit);
  ng_rb_tree_node_delete(&m3, fruit_deinit);
  ng_rb_tree_node_delete(&m4, fruit_deinit);
  ng_rb_tree_node_delete(&m5, fruit_deinit);
  ng_rb_tree_node_delete(&m6, fruit_deinit);
}


// double rotate node     Returns 1 if successful.
//    
//    
//         C       <=== dir=0   B    <=== dir=0        B
//        / \                 /   \                  /   \
//       b   d               A     C                A     D
//      / \  | \            / \    | \            / |     / \
//     A   3 4  E          1   2   3   d         1  2    c   E
//    / \      | \                    /  \             / |   | \
//   1   2     5  6                  4    E           3  4   5  6
//                                       / \
//                                      5   6


// Test left double rotation of node
TEST(NgRBTRotateTest, RotLeftDouble)
{
  // create right tree
  ng_rb_tree_node_t* A2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* D2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"D",fruit_cp_init);
  ng_rb_tree_node_t* E2 = ng_rb_tree_node_new(0x0, 0x0,
					     2,(void*)"E",fruit_cp_init);
  
  ng_rb_tree_node_t* m1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"1",fruit_cp_init);
  
  ng_rb_tree_node_t* m2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"2",fruit_cp_init);
  
  ng_rb_tree_node_t* m3 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"3",fruit_cp_init);
  
  ng_rb_tree_node_t* m4 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"4",fruit_cp_init);
  
  ng_rb_tree_node_t* m5 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"5",fruit_cp_init);
  
  ng_rb_tree_node_t* m6 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"6",fruit_cp_init);
  ng_rb_tree_t tree2;
  tree2.root_   =  B2;
  B2->kids_[0]  =  A2;
  B2->kids_[1]  =  D2;
  
  A2->kids_[0]  =  m1;
  A2->kids_[1]  =  m2;

  D2->kids_[0]  =  C2;
  D2->kids_[1]  =  E2;
  
  C2->kids_[0]  =  m3;
  C2->kids_[1]  =  m4;
  
  E2->kids_[0]  =  m5;
  E2->kids_[1]  =  m6;

  // print tree out for fun
  if(do_print) printf("\ntree2\n");
  if(do_print) ng_rb_tree_dump(&tree2,fruit_dump);

  // create left tree
  ng_rb_tree_node_t* A1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"A",fruit_cp_init);
  ng_rb_tree_node_t* B1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"B",fruit_cp_init);
  ng_rb_tree_node_t* C1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"C",fruit_cp_init);
  ng_rb_tree_node_t* D1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"D",fruit_cp_init);
  ng_rb_tree_node_t* E1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"E",fruit_cp_init);
  
  ng_rb_tree_node_t* n1 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"1",fruit_cp_init);
  
  ng_rb_tree_node_t* n2 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"2",fruit_cp_init);
  
  ng_rb_tree_node_t* n3 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"3",fruit_cp_init);
  
  ng_rb_tree_node_t* n4 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"4",fruit_cp_init);
  
  ng_rb_tree_node_t* n5 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"5",fruit_cp_init);
  
  ng_rb_tree_node_t* n6 = ng_rb_tree_node_new(0x0, 0x0,
					      2,(void*)"6",fruit_cp_init);
  
  
  ng_rb_tree_t tree1;
  tree1.root_ = C1;
  C1->kids_[0]     = B1;
  C1->kids_[1]     = D1;
  
  B1->kids_[0]     = A1;
  B1->kids_[1]     = n3;

  A1->kids_[0]     = n1;
  A1->kids_[1]     = n2;
  
  D1->kids_[0]     = n4;
  D1->kids_[1]     = E1;

  E1->kids_[0]     = n5;
  E1->kids_[1]     = n6;

  B1->red_ = true;
  D1->red_ = true;
  
  if(do_print) printf("before rotation: tree1=\n");
  if(do_print) ng_rb_tree_dump(&tree1,fruit_dump);
  
  // before rotation, they should not be structurally
  // equivalent
  EXPECT_FALSE(ng_rb_tree_node_structurally_equivalent(B2,
						       C1,
						       fruit_equal));
  
  // double rotate left!!
  tree2.root_ = ng_rb_tree_rotate_double_(B2,0);
  
  // print tree out for fun
  if(do_print) printf("after rotation\n");
  if(do_print) ng_rb_tree_dump(&tree2,fruit_dump);
  
  // after rotation, left should be strutrually
  // equivalent to right.
  EXPECT_TRUE(ng_rb_tree_structurally_equivalent(&tree2,
						 &tree1,
						 fruit_equal));
  
  // Root node should be black
  EXPECT_FALSE(tree1.root_->red_);
  // its kids should be red
  EXPECT_TRUE(tree1.root_->kids_[0]->red_);
  EXPECT_TRUE(tree1.root_->kids_[1]->red_);
  
  ng_rb_tree_node_delete(&A1, fruit_deinit);
  ng_rb_tree_node_delete(&B1, fruit_deinit);
  ng_rb_tree_node_delete(&C1, fruit_deinit);
  ng_rb_tree_node_delete(&D1, fruit_deinit);
  ng_rb_tree_node_delete(&E1, fruit_deinit);
  
  ng_rb_tree_node_delete(&A2, fruit_deinit);
  ng_rb_tree_node_delete(&B2, fruit_deinit);
  ng_rb_tree_node_delete(&C2, fruit_deinit);
  ng_rb_tree_node_delete(&D2, fruit_deinit);
  ng_rb_tree_node_delete(&E2, fruit_deinit);
  
  ng_rb_tree_node_delete(&n1, fruit_deinit);
  ng_rb_tree_node_delete(&n2, fruit_deinit);
  ng_rb_tree_node_delete(&n3, fruit_deinit);
  ng_rb_tree_node_delete(&n4, fruit_deinit);
  ng_rb_tree_node_delete(&n5, fruit_deinit);
  ng_rb_tree_node_delete(&n6, fruit_deinit);
  
  ng_rb_tree_node_delete(&m1, fruit_deinit);
  ng_rb_tree_node_delete(&m2, fruit_deinit);
  ng_rb_tree_node_delete(&m3, fruit_deinit);
  ng_rb_tree_node_delete(&m4, fruit_deinit);
  ng_rb_tree_node_delete(&m5, fruit_deinit);
  ng_rb_tree_node_delete(&m6, fruit_deinit);
}


// Test single insertion/deletion
TEST(NgRBTInsertTest, emptyTreeInsertDelete)
{
  // test initialization of tree is ok
  ng_rb_tree_t tree;
  ng_rb_tree_init(&tree);
  EXPECT_EQ(0,tree.count_);
  EXPECT_EQ(0x0,tree.root_);
  
  // insert one fruit:
  const char* x="X";
  ng_rb_tree_insert(&tree, 2,(void*)x, fruit_cp_init,fruit_compare);
  EXPECT_EQ(1,tree.count_);
  EXPECT_NE((const ng_rb_tree_node_t*)0x0,tree.root_);
  EXPECT_EQ(0, fruit_compare(tree.root_->fruit_, x));
  
  // now delete it.
  ng_rb_tree_remove(&tree,
		    2,(void*)x,fruit_cp_init,fruit_deinit,fruit_compare);
  EXPECT_EQ((const ng_rb_tree_node_t*)0x0,tree.root_);
  EXPECT_EQ(0,tree.count_);
  
  // free memory
  ng_rb_tree_deinit(&tree,fruit_deinit);
}


// Test single insertion/deletion
TEST(NgRBTInsertTest, trickyCaseTreeInsertDelete)
{
  // test initialization of tree is ok
  ng_rb_tree_t tree;
  ng_rb_tree_init(&tree);

  //          dummy_node
  //               \    dir2= right
  //              tree.root_ p(b)
  //                 /  prev_dir = left
  //              d(r)                     parent
  //                \   dir=right
  //                  i(r)                 me
  
  // insert one fruit:
  const char* p="p";
  const char* d="d";
  const char* i="i";
  
  ng_rb_tree_insert(&tree, 2,(void*)p, fruit_cp_init,fruit_compare);
  ng_rb_tree_insert(&tree, 2,(void*)d, fruit_cp_init,fruit_compare);
  if(do_print) if(do_print) printf("before:\n");
  if(do_print) ng_rb_tree_dump(&tree, fruit_dump);
  if(do_print) printf("after before:\n");
  
  ng_rb_tree_insert(&tree, 2,(void*)i, fruit_cp_init,fruit_compare);
  
  if(do_print) printf("after:\n");
  if(do_print) ng_rb_tree_dump(&tree, fruit_dump);
  if(do_print) printf("after after:\n");
  
  // free memory
  ng_rb_tree_deinit(&tree,fruit_deinit);
}


// Test random insertion/deletion
TEST(NgRBTInsertTest, randomTreeInsertDelete)
{
  // keeps track of whether this is in the set or not
  bool set[26];
  for(int i=0;i<26;i++){
    // in the beginning, none of them are in the set
    set[i] = false;
  }
  
  // test initialization of tree is ok
  ng_rb_tree_t tree;
  ng_rb_tree_init(&tree);
  EXPECT_EQ(0,tree.count_);
  EXPECT_EQ(0x0,tree.root_);
  
  // insert or delete fruit
  bool inserting = true;
  
  char bluf[2048];
  
  char x[2];
  x[1] = 0x0;
  for(int i=0;i<9999;i++){
    // generate a random lower-case letter
    x[0] = rand() % 26 + 'a';
    
    // save old count so we can test if its being
    // maintained correctly through insert and delete
    const int save_count = tree.count_;
    const bool in_set = set[x[0]-'a'];
    
    EXPECT_EQ(tree.count_,ng_rb_tree_count_nodes_recursive(&tree));
    
    if(inserting){
      // we are inserting
      ng_rb_tree_insert(&tree, 2,(void*)x, fruit_cp_init,fruit_compare);
      
      // tree should at least correct after inserting
      EXPECT_GT(ng_rb_tree_node_correct(tree.root_),0);
      
      if(in_set){
	EXPECT_EQ(tree.count_,ng_rb_tree_count_nodes_recursive(&tree));
	EXPECT_EQ(tree.count_,save_count);
	if(tree.count_ != save_count){
	  printf("break here 1");
	}
      } else {
	EXPECT_EQ(tree.count_,save_count+1);
	EXPECT_EQ(tree.count_,ng_rb_tree_count_nodes_recursive(&tree));
	set[x[0]-'a'] = true;
	if(tree.count_ != save_count+1){
	  printf("break here 2");
	}
      }
    } else {
      // we are deleting
      ng_rb_tree_remove(&tree,
			2,(void*)x,
			fruit_cp_init,fruit_deinit,fruit_compare);
      // tree should at least be correct after deleting
      EXPECT_GT(ng_rb_tree_node_correct(tree.root_),0);
      
      if(in_set) {
	EXPECT_EQ(tree.count_, save_count-1);
	EXPECT_EQ(tree.count_,ng_rb_tree_count_nodes_recursive(&tree));
	set[x[0]-'a'] = false;
	if(tree.count_ != save_count-1){
	  printf("break here 3");
	}
      } else {
	EXPECT_EQ(tree.count_,save_count);
	EXPECT_EQ(tree.count_,ng_rb_tree_count_nodes_recursive(&tree));
	if(tree.count_ != save_count){
	  printf("break here 4");
	}
      }
    }
    
    // if we don't have anything in the tree, change to
    // inserting mode.
    if(0==tree.count_){
      inserting = true;
    }
    
    //  If the tree is full, change to deleting mode
    if(26==tree.count_){
      inserting=false;
    }
  }
  
  // verify that the tree has the correct stuffs in it 
  for(int i=0;i<26;i++){
    x[0] = i+'a';
    EXPECT_EQ(set[i], ng_rb_tree_member(&tree, x,fruit_compare));
  }
  
  if(do_print) printf("random tree:\n");
  if(do_print) ng_rb_tree_dump(&tree, fruit_dump);
  
  // free memory
  ng_rb_tree_deinit(&tree,fruit_deinit);
}
