#include <ng_rb_tree.h>

#include<stdio.h>
#include<stdlib.h>

#include <ng_rb_tree_node.h>


//------------
// public api
//------------
  
// constructor
ng_rb_tree_t* ng_rb_tree_new()
{
  // allocate space for the new tree
  ng_rb_tree_t* self = (ng_rb_tree_t*)malloc(sizeof(ng_rb_tree_t));
  if(0x0 == self) return 0x0;

  // initialize the fields
  self->root_ = 0x0;
  self->count_ = 0;

  return self;
}
  
// destructor
void ng_rb_tree_delete(ng_rb_tree_t** selfp,
		       void (*uninit_fruit)(void*))
{
  // delete the tree from the root
  ng_rb_tree_node_delete_recursive(&(*selfp)->root_, uninit_fruit);
  
  // free self
  free(*selfp);

  // and zero out
  *selfp = (ng_rb_tree_t*)0x0;
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

// insertion/deletion

// insertion
const ng_rb_tree_node_t*
ng_rb_tree_insert(ng_rb_tree_t* self,
		  
		  const size_t fruit_size,
		  void*fruit,
		  void*(*fruit_cp_init)(const void*,
					void*),
		  int(*fruit_compare)(const void*,
				      const void*));
{
  // see if the tree is empty
  if(0x0==self->root_){
    self->root_ = ng_rb_tree_node_new(0x0,0x0,
				      fruit_size,fruit,fruit_cp_init);
    // no need to blacken: the nodes are by default black.
    return self->root_;
  }

  // sentinal
  ng_rb_tree_node_t dummy_node;
  ng_rb_tree_node_init(&dummy_node, 0x0,0x0, 0,0x0,0x0);
  
  ng_rb_tree_node_t* grandparent;
  ng_rb_tree_node_t* great_grandparent;
  
  ng_rb_tree_node_t* parent;  
  ng_rb_tree_node_t* me;
  
  bool dir=0;
  bool last;
  
  // set up helpers
  great_grandparent = &dummy_node;
  grandparent = 0x0;
  parent      = 0x0;
  me      = tree->root_;
  great_grandparent->kids_[1] = me;
  
  // search down the tree.
  for(;;) {
    if(0x0==me){
      // we've found our way to the leaves of the tree.  So just add the new node
      me = ng_rb_tree_node_new(0x0,0x0, fruit_size, fruit_cp_init);
      parent->kids_[dir] = me;
      if(0x0==q) return 0x0;
    } else {
      // if the kids are both red, swap color.  Note, every
      // node always has two children.  Nulls are children too.
      if(ng_rb_tree_node_is_red(q->kids_[0])
	 &&
	 ng_rb_tree_node_is_red(q->kids_[1])){
	// make this one red, and its kids black
	q->red_ = true;
	// note, we know both kids are non-null, because
	// they are red.
	q->kids_[0]->red_ = false;
	q->kids_[1]->red_ = false;
      }
    }
    
    // fix red violation
    if(q->red_ && p->red_){
      // the direction  is based on where the grandparent is.
      const int dir2 = (great_grandparent->kids_[1] == grandparent);
      
      if(q == p->kids_[last]){
	great_grandparent->kids_[dir2] = ng_rg_tree_rotate_(grandparent, !last);
      } else {
	great_grandparent->kids_[dir2] = ng_rg_tree_rotate_double_(grandparent, !last);
      }
    }
    
    // compare fruit with we are
    const int cmp = fruit_compare(q->fruit, fruit);
    
    // stop if we find it already in the tree
    if(0==cmp) break;
    
    last = dir;
    dir  = (cmp < 0);
    
    // update helpers
    if(0x0 != grandparent){
      great_grandparent=grandparent;
    }
    
    grandparent = great_grandparent;
    great_grandparent = q;
    q = q->kids_[dir];
    
    // update sentinal
    self->root_ = dummy_node->kids_[1];
  }
  
  // blacken the root node
  tree->root_->red_ = false;
}



//------------------
// private functions
//------------------

// rotate node     Returns 1 if successful.
//
//       Q    <=== dir=0    P
//      / \   dir=1 ===>   / \
//     P   C              A   Q
//    / \                    / \
//   A   B                  B   C

ng_rb_tree_node_t* ng_rb_tree_rotate_(ng_rb_tree_node_t* PQ,
				      const int dir)
{
  // do the rotation
  ng_rb_tree_node_t* QP  =  PQ->kids_[!dir];
  ng_rb_tree_node_t* B   =  QP->kids_[dir];
  PQ->kids_[!dir]        =  B;
  QP->kids_[dir]         =  PQ;

  // change the colors
  PQ->red_ = 1;
  QP->red_ = 0;

  return QP;
}


ng_rb_tree_node_t* ng_rb_tree_rotate_double_(ng_rb_tree_node_t* node,
					    const int dir)
{
  node->kids_[!dir] = ng_rb_tree_rotate_(node->kids_[!dir], !dir);
  return ng_rb_tree_rotate_(node,dir);
}

  
  
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
   
