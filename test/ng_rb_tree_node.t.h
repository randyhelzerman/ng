#ifndef NG_RB_TREE_NODE_T__H
#define NG_RB_TREE_NODE_T__H

#include <ng_rb_tree_node.h>

#include<stdbool.h>
#include<stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

  // debugging
  
  // comparison
  
  // returns true if two trees have the same tree structure
  // if the function pointer "fruit_equal" isn't null,
  // then the corresponding fruit are also compared for
  // equality using the supplied function.
  bool
  ng_rb_tree_node_structurally_equivalent(const ng_rb_tree_node_t* n1,
					  const ng_rb_tree_node_t* n2,
					  int(*fruit_equal)(const void*,
							    const void*));
  
  // tests a tree to make sure the rb laws are satisfied
  // returns red-height of tree if tree is correct; else
  // returns 0
  int ng_rb_tree_node_correct(const ng_rb_tree_node_t* node);
  
  
  void ng_rb_tree_node_dump(const ng_rb_tree_node_t* self,
                            void (*fruit_dump)(const void*));
  
  int ng_rb_tree_node_count_nodes_recursive(const ng_rb_tree_node_t* self);
  

  
    
#ifdef __cplusplus
};
#endif


#endif // include file guard
