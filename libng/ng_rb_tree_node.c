#include <ng_rb_tree_node.h>

#include<stdio.h>
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


// returns true if two trees have the same tree structure
// if the function pointer "fruit_equal" isn't null,
// then the corresponding fruit are also compared for
// equality using the supplied function.
bool
ng_rb_tree_node_structurally_equivalent(const ng_rb_tree_node_t* n1,
					const ng_rb_tree_node_t* n2,
					int(*fruit_equal)(const void*,
							  const void*))
{
  // handle null case
  if(0x0 == n1 && 0x0 == n2){ return true; }
  if(0x0 == n1 && 0x0 != n2){ return false; }
  if(0x0 != n1 && 0x0 == n2){ return false; }
  
  // colors have to be equal:
  if(n1->red_ != n2->red_) return false;
  
  // if we have a fruit equality function, use it
  // here to see if these two nodes are fruit-equal
  if(0x0 != fruit_equal){
    if(!fruit_equal(n1->fruit_,n2->fruit_)) return false;
  }
  
  // test left branch
  if(!ng_rb_tree_node_structurally_equivalent(n1->kids_[0],
					      n2->kids_[0],
					      fruit_equal)){
    return false;
  }
  
  // test right branch
  if(!ng_rb_tree_node_structurally_equivalent(n1->kids_[1],
					      n2->kids_[1],
					      fruit_equal)){
    return false;
  }
  
  // have to admit it, they are structurally equivalent.
  return true;
}


// tests a tree to make sure the rb laws are satisfied
// returns red-height of tree if tree is correct; else
// returns 0
int ng_rb_tree_node_correct(const ng_rb_tree_node_t* node)
{
  if(0x0 == node) return 1;
  
  ng_rb_tree_node_t* ln = node->kids_[0];
  ng_rb_tree_node_t* rn = node->kids_[1];
  
  if(ng_rb_tree_node_is_red(node)
     &&
     ( ng_rb_tree_node_is_red(ln)
       ||
       ng_rb_tree_node_is_red(rn))){
    printf("red violation\n");
    return 0;
  }
  
  const int lh = ng_rb_tree_node_correct(ln);
  const int rh = ng_rb_tree_node_correct(rn);
  
  if(0!=lh && 0!=rh && lh!=rh){
    printf("Black height mismatch\n");
    return 0;
  }
  
  if(lh!=0 && rh!=0){
    return ng_rb_tree_node_is_red(node) ? lh : lh+1;
  }

  return 0;
}
    

// dumper.  Takes a node, and an optional
// pointer to a dumper for the fruit, and
// dumps this node.
void ng_rb_tree_node_dump(const ng_rb_tree_node_t* self,
			  void (*fruit_dump)(const void*))
{
  if(0x0 != fruit_dump){
    fruit_dump(self->fruit_);
    printf("(%c)", self->red_ ? 'r' : 'b');
  } else {
    printf("node:%p left:%p right %p ", 
	   (void*)self, 
	   self->kids_[0], 
	   self->kids_[1]);
  }
}

