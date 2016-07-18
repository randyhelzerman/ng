#ifndef NG_RB_TREE_T___H
#define NG_RB_TREE_T___H

#include<ng_rb_tree_node.h>

#ifdef __cplusplus
extern "C" {
#endif


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
  
  int ng_rb_tree_count_nodes_recursive(const ng_rb_tree_t* self);
  
  // comparison
  
  // returns true if two trees have the same tree structure
  // if the function pointer "fruit_equal" isn't null,
  // then the corresponding fruit are also compared for
  // equality using the supplied function.
  int ng_rb_tree_structurally_equivalent(const ng_rb_tree_t* t1,
					 const ng_rb_tree_t* t2,
					 int(*fruit_equal)(const void*,
							   const void*));
  
#ifdef __cplusplus
};
#endif

#endif
