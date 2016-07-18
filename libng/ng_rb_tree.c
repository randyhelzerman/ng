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
  return ng_rb_tree_init(self);
}


ng_rb_tree_t* ng_rb_tree_init(ng_rb_tree_t* self)
{
  // initialize the fields
  self->root_ = 0x0;
  self->count_ = 0;
  
  return self;
}


// destructor
void ng_rb_tree_delete(ng_rb_tree_t** selfp,
                       void (*uninit_fruit)(void*))
{
  // deinit
  ng_rb_tree_deinit(*selfp, uninit_fruit);
  
  // free self
  free(*selfp);
  
  // and zero out
  *selfp = (ng_rb_tree_t*)0x0;
}


void ng_rb_tree_deinit(ng_rb_tree_t* self,
                       void (*uninit_fruit)(void*))
{
  // delete the tree from the root
  ng_rb_tree_node_delete_recursive(&self->root_, uninit_fruit);
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
                                      const void*))
{
  // see if the tree is empty
  if(0x0==self->root_){
    self->root_ = ng_rb_tree_node_new(0x0,0x0,
                                      fruit_size,fruit,fruit_cp_init);
    // no need to blacken: the nodes are by default black.
    if(0x0!=self->root_) self->count_ = 1;
    return self->root_;
  }
  
  // return value found deep in loop; cache here
  ng_rb_tree_node_t* returner;
  
  // sentinal
  ng_rb_tree_node_t dummy_node = {0};
  ng_rb_tree_node_init(&dummy_node, 0x0,0x0, 0,0x0,0x0);
  
  ng_rb_tree_node_t* great_grandparent;
  ng_rb_tree_node_t* grandparent;
  
  ng_rb_tree_node_t* parent;  
  ng_rb_tree_node_t* me;
  
  bool dir=false;
  bool prev_dir;
  
  // set up helpers
  great_grandparent = &dummy_node;
  grandparent = 0x0;
  parent      = 0x0;
  me          = self->root_;
  great_grandparent->kids_[1] = me;  // parent and grandparent are null?  
  
  // search down the tree.
  for(;;) {
    if(0x0==me){
      // we've found our way to the leaves of the tree.
      // So add the new node
      me = ng_rb_tree_node_new(0x0,0x0,
			       fruit_size,fruit,fruit_cp_init);
      if(0x0==me) return 0x0;
      
      // don't forget to color it red
      me->red_ = true;
      
      // link it in
      parent->kids_[dir] = me;
      self->count_ = self->count_ + 1;
      
      // this is the one we want to return.
      returner = me;
    } else {
      // if the kids are both red, swap color.  Note, every
      // node always has two children.  Nulls are children too.
      if(ng_rb_tree_node_is_red(me->kids_[0])
         &&
         ng_rb_tree_node_is_red(me->kids_[1])){
        // make this one red, and its kids black
        me->red_ = true;  // might introduce red-violation with parent.
        // note, we know both kids are non-null, because
        // they are red.
        me->kids_[0]->red_ = false;
        me->kids_[1]->red_ = false;
      }
    }
    
    // fix red violation
    if(ng_rb_tree_node_is_red(me) && ng_rb_tree_node_is_red(parent)){
      // the direction  is based on where the grandparent is.
      const int dir2 = (great_grandparent->kids_[1] == grandparent);
      
      if(me == parent->kids_[prev_dir]){
        great_grandparent->kids_[dir2]
	  = ng_rb_tree_rotate_(grandparent, !prev_dir);
      } else {
        great_grandparent->kids_[dir2]
	  = ng_rb_tree_rotate_double_(grandparent, !prev_dir);
      }
    }
    
    // update sentinal
    self->root_ = dummy_node.kids_[1];
    
    // compare fruit with we are
    const int cmp = fruit_compare(me->fruit_, fruit);
    
    // stop if we find it already in the tree
    if(0==cmp){
      returner = me;
      break;
    }
    
    prev_dir = dir;
    dir  = (cmp < 0);
    
    // update helpers
    if(0x0 != grandparent){
      // this fixes the null parent and grandparent we
      // initialized with
      great_grandparent=grandparent;
    }
    
    // let a new generation take over ;-)
    grandparent = parent;
    parent = me;
    me = me->kids_[dir];
  }
  
  // blacken the root node
  self->root_->red_ = false;
  
  // and return the node we just inserted,
  // or found.
  return returner;
}


bool
ng_rb_tree_remove(ng_rb_tree_t* self,
                  
                  const size_t fruit_size,
                  void*fruit,
                  void*(*fruit_cp_init)(const void*,
                                        void*),
                  void (*uninit_fruit)(void*),
                  int(*fruit_compare)(const void*,
                                      const void*))
{
  // trivial base case
  if(0x0 == self->root_) return true;
  
  // sentinal.
  ng_rb_tree_node_t dummy_node = {0};
  
  // Keep track of ancestor nodes up the tree
  ng_rb_tree_node_t* grandparent = 0x0;
  ng_rb_tree_node_t* parent      = 0x0;  
  ng_rb_tree_node_t* me          = &dummy_node; // we start on sentinal node
  me->kids_[true]                = self->root_; // sentinal's right kid is root
  
  // save the deleted node for copying into later
  ng_rb_tree_node_t *found_node = 0x0;
  
  // curr_dir is the direction of the kid I'm going to
  // traverse down.  Since my only kid right now is
  // on the right side, because we set it to the root
  // of the tree, my curr_dir is going to be right 
  bool curr_dir = true;
  
  //  Search and push a red down
  while (0x0 != me->kids_[curr_dir]) {
    // move to a new generation.  If this is the first
    // time through the loop, it means moving off of the
    // dummy node onto a real node.
    grandparent = parent;
    parent = me;
    me = me->kids_[curr_dir];
    
    // prev_dir is the direction my parent went to traverse
    // to me.
    bool prev_dir = curr_dir;
    
    // Now we have to find the new value of curr_dir.
    // We do this by comparing the fruit to be deleted
    // with my fruit.
    const int cmp = fruit_compare(fruit,me->fruit_);
    
    // If my fruit is equal to the fruit to be deleted,
    // then cache the found node for future recycling.
    if(0 == cmp) found_node = me;
    
    // if the fruit to be deleted is less than my fruit,
    // then search on the left kid.  Else search on the right.
    curr_dir = (cmp>=0);
    
    // Push the red node down.  I.E., don't leave this
    // loop until either: "me" is a red node or
    // the kid I'm traversing towards is a red node.
    
    // if I'm already red, then the red node has already been
    // pushed down, so bail.
    if(ng_rb_tree_node_is_red(me)) continue;

    // why bother turning this node red, when the kid I'm
    // moving towards is already red?
    if(ng_rb_tree_node_is_red(me->kids_[curr_dir])) continue;

    // The above two conditions guarantee that:
    // 1.  I'm black.
    // 2.  The node I'm moving towards is black, and (less obviously)
    // 3.  My parent is red ;-)  If it were black, then I would
    //     be red by the previous condition, and therefore
    //     would have been skipped over due to the condition
    //     before that :-)
    
    // if my other kid is red, then we can turn me into a red
    // node just by a single rotate:
    if(ng_rb_tree_node_is_red(me->kids_[!curr_dir])) {
      //
      //   say curr_dir is right; pref_dir = left:
      //
      //        parent                parent
      //       /                     /
      //     Me             =>   Kid
      //    /  \                    \
      //  kid  Kid                   me
      //                               \
      //                                Kid
      //
      parent->kids_[prev_dir] = ng_rb_tree_rotate_(me, curr_dir);
      // note black height of tree is unchanged.

      // parent doesn't point at me anymore after the rotation;
      // fix this.
      parent = parent->kids_[prev_dir];
      
      // I'm red, tree is correct, mission accomplished, so continue.
      continue;
    }
    
    // now we know that I'm black, and both my kids are black.
      
    // Need to know the color of my sibling:
    ng_rb_tree_node_t *sibling = parent->kids_[!prev_dir];
    
    if(0x0 == sibling){
      //   say curr_dir is right; pref_dir = left:
      //
      //        parent 
      //       /          
      //     Me           
      //    /  \
      //  Kid1  Kid2
      continue;
      // ok, lets think about this.  Why is this remotely ok to do?
      // I'm still black.  Well, since parent has only one more
      // black node on the other branch (a nil sibling)
      // then the branch I'm on can only have one more black
      // node.
      //
      // but...me is not null.  This means that at the very least,
      // there has to be another black node on my path than on the
      // sibling path.
      //
      // I think the only way this is possible is if the parent is
      // the dummy node.  i.e. Me is the root node of the tree.
    }
    
    // see if we can get by with just a simple color flip...
    if (!ng_rb_tree_node_is_red(sibling->kids_[!prev_dir])
        &&
        !ng_rb_tree_node_is_red(sibling->kids_[prev_dir])) {
      //   say curr_dir is right; prev_dir = left
      //
      //         parent 
      //       /         \
      //     Me            Sibling
      //    /  \             /   \
      //  Kid1  Kid2     Kid3   Kid4
      
      // color flip.  Change one parent for two red kids. we know
      // the parent was red, because it used to be me and the last
      // iteration we made me red
      parent->red_  =  false;
      sibling->red_   =  true;
      me->red_      =  true;
      
      // we are all done, because I'm now red and we
      // haven't changed the black-height of the tree.
      continue;
    }
    
    // We can blatently de-refrence the granparent pointer,
    // because in the worst case, it will point to the
    // sentinal node, which is guaranteed to have its right
    // kid set corretly.
    const bool prev_prev_dir = grandparent->kids_[true] == parent;
    
    if (ng_rb_tree_node_is_red(sibling->kids_[prev_dir])) {
      grandparent->kids_[prev_prev_dir]
	= ng_rb_tree_rotate_double_(parent, prev_dir);
    } else {
      if (ng_rb_tree_node_is_red(sibling->kids_[!prev_dir])) {
        //   say curr_dir is right; prev_dir = left; prev_prev_dir is right;
        //    [Gg]randparent              [Gg]randparent          
        //            \                         \
        //         parent          ===>         Sibling*
        //       /         \                   /       \
        //     Me           Sibling         parent    kid4
        //    /  \          /   \            /   \
        //  Kid1  Kid2     Kid3   kid4     Me    Kid3     
        //                                / \
        //                              Kid1 Kid2       
        grandparent->kids_[prev_prev_dir]
	  = ng_rb_tree_rotate_(parent, prev_dir);
      }
    }
    
    // patch up colors.  note we have to do eveyrthing
    // relative from grandparent, because all the other links have been
    // scrambled due to rotation.

    //   say curr_dir is right; prev_dir = left; prev_prev_dir is right;
    //    [Gg]randparent              [Gg]randparent*         [Gg]randparent*
    //        \                              \                     \
    //         parent          ===>         Sibling*    ===>      sibling*
    //       /         \                    /     \                /   \
    //     Me           Sibling         parent    kid4          Parent  Kid4
    //    /  \           /   \          /   \                  /  \
    //  Kid1  Kid2     Kid3   kid4     Me    Kid3              me   Kid3
    //                                / \                     / \
    //                              Kid1 Kid2               Kid1  Kid2
    me->red_ = true;
    grandparent->kids_[prev_prev_dir]->red_ = true;
    grandparent->kids_[prev_prev_dir]->kids_[0]->red_  = false;
    grandparent->kids_[prev_prev_dir]->kids_[1]->red_  = false;
  }
  
  //  Replace and remove if found
  if(0x0!=found_node){
    // copy my fruit into the node which would have been deleted
    if(me != found_node) fruit_cp_init(&me->fruit_,
				       &found_node->fruit_);
    
    // splice myself out of the tree
    parent->kids_[parent->kids_[true] == me]
      = me->kids_[0x0 == me->kids_[0]];
    
    // release my memory.
    ng_rb_tree_node_delete(&me, uninit_fruit);
    
    // one less node in tree
    self->count_ = self->count_ - 1;
  }
  
  // update root.  Remember, it was set to
  // sentinal node's right kid.
  self->root_ = dummy_node.kids_[true];
  
  // blacken the root
  if(0x0 != self->root_) self->root_->red_ = false;
  
  // success?
  return true;
}


//-------
// access
//-------

// returns true if in tree
bool ng_rb_tree_member(const ng_rb_tree_t* self,
		       void* fruit,
		       int(*fruit_compare)(const void*,
					   const void*))
{
  return ng_rb_tree_node_member(self->root_,fruit,fruit_compare);
}


const void* ng_rb_tree_lookup(const ng_rb_tree_t* self,
			      void* fruit,
			      int(*fruit_compare)(const void*,
						  const void*))
{
  return ng_rb_tree_node_lookup(self->root_,fruit,fruit_compare)->fruit_;
}


// do an in-order recursive visit to each node in the tree and call
// the visitor function on each of the fruits
void ng_rb_tree_visit(const ng_rb_tree_t* self,
		      void(*visitor)(const void*))
{
  return ng_rb_tree_node_visit(self->root_,visitor);
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

  QP->kids_[dir]         =  PQ;
  PQ->kids_[!dir]        =  B;

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

  
  
