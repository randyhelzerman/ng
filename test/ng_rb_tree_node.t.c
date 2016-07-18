#include <ng_rb_tree_node.h>
#include <ng_rb_tree_node.t.h>

#include <stdio.h>
#include <stdbool.h>

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
  if(0x0 == n1 && 0x0 == n2){ return true;  }
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

int ng_rb_tree_node_count_nodes_recursive(const ng_rb_tree_node_t* self)
{
  if(0x0==self) return 0;
  
  return
    1 + ng_rb_tree_node_count_nodes_recursive(self->kids_[0])
    + ng_rb_tree_node_count_nodes_recursive(self->kids_[1]);
}
