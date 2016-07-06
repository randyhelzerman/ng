#ifndef NG_RB_TREE_NODE__H
#define NG_RB_TREE_NODE__H

#include<stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

  // represents a node in a red-black tree.
  typedef struct ng_rb_tree_node {
    int                          red_;
    struct ng_rb_tree_node*      kids_[2];     // left is 0, right is 1
    char                         fruit_[];     // the "fruit" i.e. the valuable thing which 
                                               // is on the brances of the tree
  } ng_rb_tree_node_t;
  
  
  // constructor
  // fruit         is a pointer to the fruit to be stored
  // fruit_size    is sizeof(fruit)
  // fruit_cp_init takes a pointer to a pre-existing fruit,
  //               and a pointer to a region of memory,  and
  //               copies the data from the pre-existing fruit
  //               to the region of memory.
  ng_rb_tree_node_t* ng_rb_tree_node_new(ng_rb_tree_node_t* left,
                                         ng_rb_tree_node_t* right,
					 
					 const size_t fruit_size,
                                         void* fruit,
					 void* (*fruit_cp_init)(const void*,
								void*));

  ng_rb_tree_node_t* ng_rb_tree_node_init(ng_rb_tree_node_t*self,
					  
					  ng_rb_tree_node_t* left,
					  ng_rb_tree_node_t* right,
					  
					  const size_t fruit_size,
					  void* fruit,
					  void* (*fruit_cp_init)(const void*,
								 void*));
  
  // destructors
  // just delete self
  void ng_rb_tree_node_delete(ng_rb_tree_node_t** selfp,
                              void (*uninit_fruit)(void*));

  void ng_rb_tree_node_uninit(ng_rb_tree_node_t* self,
                              void (*uninit_fruit)(void*));

  // delete self + all kids recursively
  void ng_rb_tree_node_delete_recursive(ng_rb_tree_node_t** selfp,
					void (*uninit_fruit)(void*));

  // accessors

  // 1 if the node is red, 0 if its black
  int ng_rb_tree_node_is_red(const ng_rb_tree_node_t* self);
  

  // comparison
  
  // returns true if two trees have the same tree structure
  // if the function pointer "fruit_equal" isn't null,
  // then the corresponding fruit are also compared for
  // equality using the supplied function.
  int ng_rb_tree_node_structurally_equivalent(const ng_rb_tree_node_t* n1,
					      const ng_rb_tree_node_t* n2,
					      int(*fruit_equal)(const void*,
								const void*));
    
  
  void ng_rb_tree_node_dump(const ng_rb_tree_node_t* self,
                            void (*fruit_dump)(const void*));
  
  
#ifdef __cplusplus
};
#endif


#endif
