#include <ng_nfa.h>


// constructors
ng_nfa_t* ng_nfa_new()
{
  ng_nfa_t* self = (ng_nfa_t*)malloc(sizeof(ng_nfa_t));
  return ng_nfa_init(self);
}

ng_nfa_t* ng_nfa_init(ng_nfa_t* self)
{
  return *self;
}
  
// destructors
void ng_nfa_delete(ng_nfa_t** selfp)
{
  ng_nfa_deinit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_fa_deinit(ng_nfa_t* self)
{
}
  
// access

// adds a new state. Returns its state number
int ng_nfa_add_state(ng_nfa_t* self)
{
}

// adds a a transition to a state.  This is a very
// low-level function, probably not the one you want.
void ng_nfa_add_transition(const char* , const int new_state)
{
}

  
// debugging
void ng_nfa_dump(const ng_nfa_t* self)
{
  printf("NFA\n");
}
			     
