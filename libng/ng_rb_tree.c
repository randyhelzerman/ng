#include <ng_rb_tree.h>

#include<stdio.h>
#include<stdlib.h>

#include <ng_rb_tree_node.h>


//------------
// public api
//------------
  
// constructor
ng_rb_tree_t* ng_rb_tree_new()
{
  // allocate space for the new tree
  ng_rb_tree_t* self = (ng_rb_tree_t*)malloc(sizeof(ng_rb_tree_t));
  if(0x0 == self) return 0x0;

  // initialize the fields
  self->root_ = 0x0;
  self->count_ = 0;

  return self;
}
  
// destructor
void ng_rb_tree_delete(ng_rb_tree_t** selfp,
		       void (*delete_fruit)(void**))
{
  // delete the tree from the root
  ng_rb_tree_node_delete_recursive(&(*selfp)->root_, delete_fruit);
  
  // free self
  free(*selfp);

  // and zero out
  *selfp = (ng_rb_tree_t*)0x0;
}


//------------------
// private functions
//------------------

// rotate node right.  Returns 1 if successful.
//
//      root              root
//       |                 |
//       Q                 P
//      / \     ===>      / \
//     P   C             A   Q
//    / \                   / \
//   A   B                 B   C

int ng_rb_tree_rotate_node_right(ng_rb_tree_node_t** root)
{
  // insanity check
  if(0x0 == root) return 0;
  
  // unpack
  ng_rb_tree_node_t* Q = *root;
  if(0x0 == Q) return 0;
  ng_rb_tree_node_t* P = Q->left_;
  if(0x0 == P) return 0;
  
  // Its ok if this is null--won't
  // be traversed, just copied around.
  ng_rb_tree_node_t* B = P->right_;
  
  // now re-arrange
  *root     =  P;   P->parent_ = *root;
  P->right_ =  Q;   Q->parent_ = P;
  Q->left_  =  B;   B->parent_ = Q;
  
  // success!
  return 1;
}

  
// rotate node left.  Returns 1 if successful.
//
//      root              root
//       |                 |
//       Q                 P
//      / \     <===      / \
//     P   C             A   Q
//    / \                   / \
//   A   B                 B   C

int ng_rb_tree_rotate_node_left(ng_rb_tree_node_t** root)
{
  // insanity check
  if(0x0 == root) return 0;
  
  // unpack
  ng_rb_tree_node_t* P = *root;
  if(0x0 == P) return 0;
  ng_rb_tree_node_t* Q = P->right_;
  if(0x0 == Q) return 0;
  
  // Its ok if this is null--won't
  // be traversed, just copied around.
  ng_rb_tree_node_t* B = Q->left_;
  
  // now re-arrange
  *root     =  Q;    Q->parent_ = *root;
  Q->left_  =  P;    P->parent_ = Q;
  P->right_ =  B;    B->parent_ = P;
  
  // success!
  return 1;
}
  
  
//--------------
// for debugging
//--------------

// dump tree to stdout in halfway readable format
void ng_rb_tree_dump(const ng_rb_tree_t* self,
		     void (*fruit_dump)(const void*))
{
  ng_rb_tree_dump_aux(self->root_, 0, fruit_dump);
}


// helper function for the above
void ng_rb_tree_dump_aux(const ng_rb_tree_node_t* self,
			 const int indent,
			 void (*fruit_dump)(const void*))
{
  // old prolog trick for printing out trees
  
  //dump right tree
  ng_rb_tree_dump_aux(self->right_, indent+5, fruit_dump);
  
  // dump self.  first tab over:
  for(int i=0;i<indent;i++) { printf(" "); }
  // then dump self node + fruit
  ng_rb_tree_node_dump(self, fruit_dump);
  printf("\n");
  
  // and finally dump left tree
  ng_rb_tree_dump_aux(self->left_, indent+5, fruit_dump);
}
   
