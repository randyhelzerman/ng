#include <ng_rb_tree_node.h>

#include<stdlib.h>

//------------
// node stuffs
//------------

// constructor
ng_rb_tree_node_t* ng_rb_tree_node_new(ng_rb_tree_node_t* left,
				       ng_rb_tree_node_t* right,
					 
				       const size_t fruit_size,
				       void* fruit,
				       void* (*fruit_cp_init)(const void*,
							      void*))
{
  // allocate the node if we can
  size_t node_size = sizeof(ng_rb_tree_node_t) + fruit_size;
  ng_rb_tree_node_t* self = (ng_rb_tree_node_t*)malloc(node_size);
  if(0x0==self) return 0x0;
  
  // convert the newly-aquired memory into a tree node.
  return ng_rb_tree_node_init(self, left,right, fruit_size,fruit,fruit_cp_init);
}


ng_rb_tree_node_t* ng_rb_tree_node_init(ng_rb_tree_node_t* self,
					
					ng_rb_tree_node_t* left,
					ng_rb_tree_node_t* right,
					
					const size_t fruit_size,
					void* fruit,
					void* (*fruit_cp_init)(const void*,
							       void*))
{
  // nodes default to black
  self->red_ = false;
  
  // assign the node fields
  self->kids_[0] = left;
  self->kids_[1] = right;
  
  // initialize the fruit
  if(0x0!=fruit_cp_init){
    fruit_cp_init(fruit, (void*)self->fruit_);
  }
  
  // and return the newly created node
  return self;
}


// destructor
// just delete self
void ng_rb_tree_node_delete(ng_rb_tree_node_t** selfp,
			    void (*uninit_fruit)(void*))
{
  // first uninit this
  ng_rb_tree_node_uninit(*selfp, uninit_fruit);
  
  // delete self
  free(*selfp);
  *selfp = (ng_rb_tree_node_t*)0x0;
}


void ng_rb_tree_node_uninit(ng_rb_tree_node_t* self,
			    void (*uninit_fruit)(void*))
{
  // if the delete fruit function is set, then
  // invoke it to delete the fruit
  if(0x0 != uninit_fruit){
    uninit_fruit((void*)self->fruit_);
  }
}
  

// delete self + all kids recursively.
void ng_rb_tree_node_delete_recursive(ng_rb_tree_node_t** selfp,
				      void (*uninit_fruit)(void*))
{
  // make this safe to call on a null node
  if(0x0 == *selfp) return;
  
  // delete the kids recursively.  safe to do this because
  // we just checked above :-)
  ng_rb_tree_node_delete_recursive(&(*selfp)->kids_[0],  uninit_fruit);
  ng_rb_tree_node_delete_recursive(&(*selfp)->kids_[1],  uninit_fruit);
  
  // now delete self
  ng_rb_tree_node_delete(selfp, uninit_fruit);
}


// accessors

// 1 if the node is red, 0 if its black
bool ng_rb_tree_node_is_red(const ng_rb_tree_node_t* self)
{
  return 0x0!=self && self->red_==1;
}


// returns true if in tree
bool ng_rb_tree_node_member(const ng_rb_tree_node_t* node,
			    void* fruit,
			    int(*fruit_compare)(const void*,
						const void*))
{
  while(0x0 != node){
    const int cmp = fruit_compare(fruit, node->fruit_);
    if(0x0==cmp) return true;
    node = node->kids_[cmp>0];
  }
  
  // reached tip--not in tree
  return false;
}


ng_rb_tree_node_t*
ng_rb_tree_node_lookup(ng_rb_tree_node_t* node,
		       void* fruit,
		       int(*fruit_compare)(const void*,
					   const void*))
{
  while(0x0 != node){
    const int cmp = fruit_compare(fruit, node->fruit_);
    if(0x0==cmp) return node;
    node = node->kids_[cmp>0];
  }
  
  // reached tip--not in tree
  return 0x0;
}


// do an in-order recursive visit to each node in the tree and call
// the visitor function on each of the fruits
void ng_rb_tree_node_visit(const ng_rb_tree_node_t* self,
			   void(*visitor)(const void*))
{
  if(0x0==self) return;
  
  ng_rb_tree_node_visit(self->kids_[0],visitor);
  visitor(self->fruit_);
  ng_rb_tree_node_visit(self->kids_[1],visitor);
}
