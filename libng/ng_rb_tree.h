#ifndef NG_RB_TREE___H
#define NG_RB_TREE___H

#include<ng_rb_tree_node.h>

#ifdef __cplusplus
extern "C" {
#endif
  

  typedef struct ng_rb_tree {
    ng_rb_tree_node_t* root_;    // root of the rgb tree
    int count_;                  // total number of items in the tree.  
  } ng_rb_tree_t;

  //------------
  // public api
  //------------
  
  // constructor
  ng_rb_tree_t* ng_rb_tree_new();
  
  // destructor
  void ng_rb_tree_delete(ng_rb_tree_t** self,
			 void (*delete_fruit)(void**));

  
  //------------------
  // private functions
  //------------------

  // rotate node rright
  int ng_rb_tree_rotate_node_right(ng_rb_tree_node_t** root);
  
  // rotate node left
  int ng_rb_tree_rotate_node_left(ng_rb_tree_node_t** root);
  
  
  //--------------
  // for debugging
  //--------------

  // dump tree to stdout in halfway readable format
  void ng_rb_tree_dump(const ng_rb_tree_t* self,
		       void (*fruit_dump)(const void*));
  
  // helper function for the above
  void ng_rb_tree_dump_aux(const ng_rb_tree_node_t* self,
			   const int indent,
			   void (*fruit_dump)(const void*));
  
  
#ifdef __cplusplus
};
#endif

#endif
