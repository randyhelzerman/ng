#ifndef NG_RB_TREE_NODE__H
#define NG_RB_TREE_NODE__H

#ifdef __cplusplus
extern "C" {
#endif

  // represents a node in a red-black tree.
  typedef struct ng_rb_tree_node {
    struct ng_rb_tree_node*      parent_;      // parent node in the tree
    struct ng_rb_tree_node*      left_;        // left child
    struct ng_rb_tree_node*      right_;       // right child
    void*                        fruit_;       // the "fruit" i.e. the valuable thing which 
                                               // is on the brances of the tree
  } ng_rb_tree_node_t;


  // constructor
  ng_rb_tree_node_t* ng_rb_tree_node_new(ng_rb_tree_node_t* parent,
                                         ng_rb_tree_node_t* left,
                                         ng_rb_tree_node_t* right,
                                         void* fruit);
  
  // destructors
  // just delete self
  void ng_rb_tree_node_delete(ng_rb_tree_node_t** selfp,
                              void (*delete_fruit)(void**));

  // delete self + all kids recursively
  void ng_rb_tree_node_delete_recursive(ng_rb_tree_node_t** selfp,
					void (*delete_fruit)(void**));


  // comparison
  
  // returns true if two trees have the same tree structure
  // if the function pointer "fruit_equal" isn't null,
  // then the corresponding fruit are also compared for
  // equality using the supplied function.
  int ng_rb_tree_structurally_equivalent(const ng_rb_tree_node_t* n1,
					 const ng_rb_tree_noee_t* n2,
					 int(*fruit_equal)(const void*,
							   const void*));
    
  
  void ng_rb_tree_node_dump(const ng_rb_tree_node_t* self,
                            void (*fruit_dump)(const void*));
  
  
#ifdef __cplusplus
};
#endif


#endif
