#include <ng_nfa_state.h>

#include<string.h>

#include <ng_vector.h>
#include <ng_interval.h>

// constructors
ng_nfa_state_t* ng_nfa_state_new(const char* name)
{
  // allocate the memory
  ng_nfa_state_t* self = (ng_nfa_state_t*)malloc(sizeof(ng_nfa_state_t));
  
  // initialize it
  return ng_nfa_state_init(self, name);
}


ng_nfa_state_t* ng_nfa_state_init(ng_nfa_state_t* self, const char* name)
{
  // copy over the name
  self->name_ = strdup(name);
  
  // initialize the action...nothing for now
  self->action_ = 0x0;
  
  // initialize the arcs.  I don't know what to put for initial max so
  // just pick a number.
  self->arcs_ = ng_vector_new(sizeof(ng_interval_t), 10);
  
  return self;
}

  
// destructors
void ng_nfa_state_delete(ng_nfa_state_t** selfp)
{
  ng_nfa_state_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_nfa_state_uninit(ng_nfa_state_t* self)
{
  free(self->name_);
  self->name_ = 0x0;
  
  ng_vector_delete(&(self->arcs_),
		   sizeof(ng_interval_t),
		   (void(*)(void*))ng_interval_uninit);
}


// access

// adds an interval
void ng_nfa_state_add_interval(ng_nfa_state_t* self,
			       const ng_interval_t* interval)
{
  ng_vector_push_back(&self->arcs_,
		      sizeof(ng_interval_t), (const void*)interval,
		      (void *(*)(const void *, void *))ng_interval_cp_init,
		      (void (*)(void *))ng_interval_uninit);
}


// for sorting and searching
int ng_nfa_state_compare(const ng_nfa_state_t*s1,
			 const ng_nfa_state_t*s2)
{
  return strcmp(s1->name_, s2->name_);
}

