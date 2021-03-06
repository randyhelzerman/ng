#ifndef NG_RB_TREE___H
#define NG_RB_TREE___H

#include<ng_rb_tree_node.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  
  typedef struct ng_rb_tree {
    ng_rb_tree_node_t*   root_;     // root of the rgb tree
    int                  count_;    // total number of items in the tree.  
  } ng_rb_tree_t;
  
  //------------
  // public api
  //------------
  
  // constructor
  ng_rb_tree_t* ng_rb_tree_new();
  
  ng_rb_tree_t* ng_rb_tree_init(ng_rb_tree_t* self);
  
  // destructor
  void ng_rb_tree_delete(ng_rb_tree_t** self,
			 void (*uninit_fruit)(void*));
  
  void ng_rb_tree_deinit(ng_rb_tree_t* self,
			 void (*uninit_fruit)(void*));
  
  // insertion/deletion
  
  // insertion
  const ng_rb_tree_node_t*
  ng_rb_tree_insert(ng_rb_tree_t* self,
		    
		    const size_t fruit_size,
		    void* fruit,
		    void*(*fruit_cp_init)(const void*,
					  void*),
		    int(*fruit_compare)(const void*,
					const void*));
  
  bool
  ng_rb_tree_remove(ng_rb_tree_t* self,
		    
		    const size_t fruit_size,
		    void* fruit,
		    void*(*fruit_cp_init)(const void*,
					  void*),
		    void (*uninit_fruit)(void*),
		    int(*fruit_compare)(const void*,
					const void*));
  
  
  //-------
  // access
  //-------

  // returns true if in tree
  bool
  ng_rb_tree_member(const ng_rb_tree_t* self,
		    void* fruit,
		    int(*fruit_compare)(const void*,
					const void*));
  
  // returns a pointer to the fruit if it
  // is in there, 0x0 if not.  Allows for use as a map.
  const void*
  ng_rb_tree_lookup(const ng_rb_tree_t* self,
		    void* fruit,
		    int(*fruit_compare)(const void*,
					const void*));

  
  // do an in-order recursive visit to each node in the tree
  // and call the visitor function on each of the
  // fruits
  void ng_rb_tree_visit(const ng_rb_tree_t* self,
			void(*visitor)(const void*));
  
  
  //------------------
  // private functions
  //------------------
  
  // rotate node right
  ng_rb_tree_node_t* ng_rb_tree_rotate_(ng_rb_tree_node_t* root,
					const int dir);
  
  ng_rb_tree_node_t* ng_rb_tree_rotate_double_(ng_rb_tree_node_t* node,
					       const int dir);
  
  
#ifdef __cplusplus
};
#endif

#endif
