#include <ng_vector.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// constructors
ng_vector_t* ng_vector_new(const size_t fruit_size, const int max)
{
  const size_t size = sizeof(ng_vector_t) + fruit_size*max;
  ng_vector_t* self = (ng_vector_t*)malloc(size);
  
  return ng_vector_init(self, fruit_size, max);
}


ng_vector_t* ng_vector_init(ng_vector_t* self, const size_t fruit_size, const int max)
{
  self->max_ = max;
  self->numb_ = 0;
  return self;
}


ng_vector_t* ng_vector_enlarge(ng_vector_t** selfp,
			       const size_t fruit_size,
			       void*(*fruit_cp_init)(const void*,
						     void*),
			       void(*fruit_deinit)(void*))
{
  // cache the old one
  ng_vector_t* self = *selfp;
  
  // calculate new size needed
  const int new_max = self->max_*2;
  const size_t new_size = sizeof(ng_vector_t) + new_max*fruit_size;
  
  if(0x0==fruit_cp_init){
    *selfp = (ng_vector_t*)realloc(self, new_size);
    (*selfp)->max_ = new_max;
    return *selfp;
  } else {
    // allocate new blank stuffs
    *selfp = (ng_vector_t*)malloc(new_size);
    
    // copy over the old stuffs
    for(int i=0;i<self->numb_;i++){
      const int delta = fruit_size*i;
      void *old_fruit = (void*)(self->fruits_     +  delta);
      void *new_fruit = (void*)((*selfp)->fruits_ +  delta);
      fruit_cp_init(old_fruit,new_fruit);
    }
    
    // copy over size parameters
    (*selfp)->max_ = new_max;
    (*selfp)->numb_ = self->numb_;
  }
  
  if(0x0==fruit_deinit){
    for(int i=0;i<self->numb_;i++){
      void *fruit = (void*)(self->fruits_ + fruit_size*i);
      fruit_deinit(fruit);
    }
  }
  
  // deallocate old space
  free(self);
  
  // return new
  return *selfp;
}


// destructors
void ng_vector_delete(ng_vector_t** selfp, const int fruit_size, void(*fruit_uninit)(void*))
{
  ng_vector_uninit(*selfp, fruit_size, fruit_uninit);
  free(*selfp);
  *selfp = 0x0;
}


void ng_vector_uninit(ng_vector_t* self, const int fruit_size, void(*fruit_uninit)(void*))
{
  if(0x0 != fruit_uninit){
    for(int i=0;i<self->numb_*fruit_size;i+=fruit_size){
      fruit_uninit((void*)(self->fruits_ + i));
    }
  }
  
  self->numb_=0;
}


// accesss

// just for convenience
bool ng_vector_empty(const ng_vector_t* self){
  return 0==self->numb_;
}


// get a pointer to an elment in the vector
void* ng_vector_at(ng_vector_t* self, const int index, const int fruit_size)
{
  return (void*)(self->fruits_+index*fruit_size);
}


// returns the back ("top") of th stack...
void* ng_vector_back(ng_vector_t* self, const int fruit_size)
{
  return ng_vector_at(self, self->numb_-1, fruit_size);
}

  
// add an element to the end of the vector
void
ng_vector_push_back(ng_vector_t** selfp,
		    const int fruit_size, const void* fruit,
		    void*(*fruit_cp_init)(const void*,
					  void*),
		    void(*fruit_deinit)(void*))
{
  // see if we need teo expand or not
  ng_vector_t* self = *selfp;
  if(self->numb_== self->max_){
    self = ng_vector_enlarge(selfp, fruit_size,  fruit_cp_init, fruit_deinit);
  }
  
  // calculate place to put new fruit
  void* place = (void*)(self->fruits_ + self->numb_*fruit_size);
  
  // if we don't have a copy-initializer, just bitcopy
  if(0x0 == fruit_cp_init){
    memcpy(place, fruit, fruit_size);
  } else {
    fruit_cp_init(fruit, place);
  }
  
  // bump up the pointer
  self->numb_+=1;
}


// remove an element from the end of the vector
void
ng_vector_pop_back(ng_vector_t* self,
		   const int fruit_size,
		   void(*fruit_deinit)(void*))
{
  // one less element in here
  self->numb_ -= 1;
  
  if(0x0 != fruit_deinit){
    const int position = fruit_size*self->numb_;
    fruit_deinit((void*)(self->fruits_+position));
  }
}


// binary search.  Equivalent to lower_bound in c++ STL
int ng_vector_binary_search_upper_bound(const ng_vector_t* v,
					const int l, const int h,
					const int fruit_size, const void* fruit,
					int(*fruit_compare)(const void*,
							    const void*))
{
  // initalize the low we use to the low supplied
  int low[2];
  low[0] = l;
  
  int size = (h-l);
  while(size>0){
    const int half     =  size/2;
    low[1]             =  low[0]+size-half;
    size               =  half;
    const void* probe  =  (void*)(v->fruits_ + fruit_size*(low[0]+half));
    const bool cmp     =  fruit_compare(fruit, probe) > 0;
    low[0]             =  low[cmp];
  }
  
  return low[0];
}


// binary search.  Equivalent to lower_bound in c++ STL
int ng_vector_binary_search_lower_bound(const ng_vector_t* v,
					const int l, const int h,
					const int fruit_size, const void* fruit,
					int(*fruit_compare)(const void*,
							    const void*))
{
  // initalize the low we use to the low supplied
  int low[2];
  low[0] = l;
  
  int size = (h-l);
  while(size>0){
    const int half     =  size/2;
    low[1]             =  low[0]+size-half;
    size               =  half;
    const void* probe  =  (void*)(v->fruits_ + fruit_size*(low[0]+half));
    const bool cmp     =  fruit_compare(fruit, probe) >= 0;
    low[0]             =  low[cmp];
  }
  
  return low[0];
}


// debugging
void ng_vector_dump(const ng_vector_t* self, const int fruit_size, void(*fruit_dump)(const void*))
{
  // print out basic stats
  printf("vector: numb=%d  max=%d ", self->numb_, self->max_);
  
  // if we have a dump function, dump the contents
  if(0x0 != fruit_dump){
    printf("[ ");
    for(int i=0;i<self->numb_;i++){
      const void* position = (const void*)(self->fruits_ + i*fruit_size);
      fruit_dump(position);
      printf(" ");
    }
    printf("] ");
  }
}
