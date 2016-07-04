#include <ng_rb_tree_node.h>

#include<stdio.h>
#include<stdlib.h>

//------------
// node stuffs
//------------

// constructor
ng_rb_tree_node_t* ng_rb_tree_node_new(ng_rb_tree_node_t* parent,
				       ng_rb_tree_node_t* left,
				       ng_rb_tree_node_t* right,
				       void* fruit)
{
  // allocate the node if we can
  ng_rb_tree_node_t* self= (ng_rb_tree_node_t*)malloc(sizeof(ng_rb_tree_node_t));
  if(0x0==self) return 0x0;
  
  // assign the fields
  self->parent_ = parent;
  self->left_ = left;
  self->right_ = right;
  self->fruit_ = fruit;
  
  // and return the newly created node
  return self;
}


// destructor
// just delete self
void ng_rb_tree_node_delete(ng_rb_tree_node_t** selfp,
			    void (*delete_fruit)(void**))
{
  // if the delete fruit function is set, then
  // invoke it to delete the fruit
  if(0x0 != delete_fruit){
    delete_fruit(&(*selfp)->fruit_);
  }
  
  // delete self
  free(*selfp);
  *selfp = (ng_rb_tree_node_t*)0x0;
}
  

// delete self + all kids recursively.
void ng_rb_tree_node_delete_recursive(ng_rb_tree_node_t** selfp,
				      void (*delete_fruit)(void**))
{
  // make this safe to call on a null node
  if(0x0 == *selfp) return;
  
  // delete the kids recursively.  safe to do this because
  // we just checked above :-)
  ng_rb_tree_node_delete_recursive(&(*selfp)->left_,   delete_fruit);
  ng_rb_tree_node_delete_recursive(&(*selfp)->right_,  delete_fruit);
  
  // if we want to delete the fruit, delete it too
  if(0x0 != delete_fruit){
    delete_fruit(&(*selfp)->fruit_);
  }
  
  // free self
  free(*selfp);
  
  // zero out self
  *selfp = (ng_rb_tree_node_t*)0x0;
}



// dumper.  Takes a node, and an optional
// pointer to a dumper for the fruit, and
// dumps this node.
void ng_rb_tree_node_dump(const ng_rb_tree_node_t* self,
			  void (*fruit_dump)(const void*))
{
  printf("node:%p left:%p right %p ", 
	 (void*)self, 
	 self->left_, 
	 self->right_);
  
  if(0x0 != fruit_dump){
    printf("fruit:");
    fruit_dump(self->fruit_);
  }
}

