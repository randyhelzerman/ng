#include <ng_rb_tree.h>
#include <ng_rb_tree.t.h>

#include <ng_rb_tree_node.h>
#include <ng_rb_tree_node.t.h>

#include <stdio.h>

//--------------
// for debugging
//--------------

// dump tree to stdout in halfway readable format
void ng_rb_tree_dump(const ng_rb_tree_t* self,
                     void (*fruit_dump)(const void*))
{
  ng_rb_tree_dump_aux(self->root_, 0, fruit_dump);
}


// helper function for the above
void ng_rb_tree_dump_aux(const ng_rb_tree_node_t* self,
                         const int indent,
                         void (*fruit_dump)(const void*))
{
  if(0x0 == self) return;
  
  // old prolog trick for printing out trees
  
  //dump right tree
  ng_rb_tree_dump_aux(self->kids_[1], indent+5, fruit_dump);
  
  // dump self.  first tab over:
  for(int i=0;i<indent;i++) { printf(" "); }
  // then dump self node + fruit
  ng_rb_tree_node_dump(self, fruit_dump);
  printf("\n");
  
  // and finally dump left tree
  ng_rb_tree_dump_aux(self->kids_[0], indent+5, fruit_dump);
}

int ng_rb_tree_count_nodes_recursive(const ng_rb_tree_t* self){
  return ng_rb_tree_node_count_nodes_recursive(self->root_);
}


// comparison

// returns true if two trees have the same tree structure
// if the function pointer "fruit_equal" isn't null,
// then the corresponding fruit are also compared for
// equality using the supplied function.
int ng_rb_tree_structurally_equivalent(const ng_rb_tree_t* t1,
                                       const ng_rb_tree_t* t2,
                                       int(*fruit_equal)(const void*,
                                                         const void*))
{
  if(0x0 == t1 && 0x0 == t2) { return 1; }
  if(0x0 == t1 && 0x0 != t2) { return 0; }
  if(0x0 != t1 && 0x0 == t2) { return 0; }
  
  return ng_rb_tree_node_structurally_equivalent(t1->root_,
                                                 t2->root_,
                                                 fruit_equal);
}


