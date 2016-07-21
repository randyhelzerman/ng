#include <ng_nfa_factory.h>

#include <ng_token_array.h>
#include <ng_symbol_table.h>
#include <ng_ascii_util.h>

#include <stdlib.h>
#include <string.h>


// construction
ng_nfa_factory_t* ng_nfa_factory_new()
{
  // allocate sufficient memory
  ng_nfa_factory_t* self
    = (ng_nfa_factory_t*)malloc(sizeof(ng_nfa_factory_t));
  
  // initialize it
  return ng_nfa_factory_init(self);
}


ng_nfa_factory_t* ng_nfa_factory_init(ng_nfa_factory_t* self)
{
  self->tokens_ = 0x0;
  self->symbol_table_ = ng_symbol_table_new();
  
  return self;
}


// deletion
void ng_nfa_factory_delete(ng_nfa_factory_t** selfp)
{
  // make it ok to delete a null pointer to one of thse
  if(0x0==*selfp) return;
  
  ng_nfa_factory_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_nfa_factory_uninit(ng_nfa_factory_t* self)
{
  ng_token_array_delete(&self->tokens_);
  ng_symbol_table_delete(&self->symbol_table_);
}


// access

// build an nfa from parsing the string spec
ng_nfa_t* ng_nfa_factory_build(ng_nfa_factory_t* self,
			       const char* string)
{
  // refresh the tokens stuffs
  ng_token_array_delete(&self->tokens_);
  self->tokens_ = ng_token_array_new();
  self->tokens_->string_ = string;
  
  // tokenize the tokens
  ng_nfa_factory_tokenize(self);
  
  return 0x0;
}


// tokenize the tokens
void
ng_nfa_factory_tokenize(ng_nfa_factory_t* self)
{
  self->current_ = self->tokens_->string_;
  self->end_ = self->tokens_->string_ + strlen(self->tokens_->string_);
  
  bool gogo = true;
  while(gogo){
    ng_nfa_factory_tokenize_white_space(self);
    
    gogo = (ng_nfa_factory_tokenize_non_terminal(self)
	    ||
	    ng_nfa_factory_tokenize_terminal(self)
	    ||
	    ng_nfa_factory_tokenize_arrow(self) )
      && self->current_ < self->end_;
  }
}


// consumes white-space.  Always succeeds.
bool
ng_nfa_factory_tokenize_white_space(ng_nfa_factory_t* self)
{
  while(ng_ascii_util_is_white_space(*self->current_)) {
    if(!ng_ascii_util_advance_char(&self->current_, self->end_)) return true;
  }
  
  return true;
}


bool
ng_nfa_factory_tokenize_non_terminal(ng_nfa_factory_t* self)
{
  const char* save = self->current_;
  
  // needs at least one letter to strt
  if(!ng_ascii_util_is_letter(*self->current_)){
    return false;
  }
  
  // advance
  if(!ng_ascii_util_advance_char(&self->current_, self->end_)){
    // push the token
    ng_token_array_push_back(self->tokens_,
			     save, self->current_,
			     NG_NFA_FACTORY_NON_TERMINAL);
    return true;
  }
  
  while(ng_ascii_util_is_id(*self->current_)){
    if(!ng_ascii_util_advance_char(&self->current_, self->end_)){
      // push the token
      ng_token_array_push_back(self->tokens_,
			       save, self->current_,
			       NG_NFA_FACTORY_NON_TERMINAL);
      return true;
    }
  }
  
  // push the last token
  ng_token_array_push_back(self->tokens_,
			   save, self->current_,
			   NG_NFA_FACTORY_NON_TERMINAL);
  return true;
}


bool
ng_nfa_factory_tokenize_terminal(ng_nfa_factory_t* self)
{
  // cache the beginning 
  const char* save = self->current_;
  
  // consume first quote
  if(!ng_ascii_util_is_single_quote(*self->current_)){
    return false;
  }
  
  // if we've run out of string, restore position and return false
  if(!ng_ascii_util_advance_char(&self->current_, self->end_)){
    self->current_ = save;
    return false;
  }
  
  // consume name
  while(!ng_ascii_util_is_single_quote(*self->current_)){
    // if we've run out of string, restore position and return false
    if(!ng_ascii_util_advance_char(&self->current_, self->end_)){
      self->current_ = save;
      return false;
    }
  }
  
  // consume final quote
  // consume first quote
  if(!ng_ascii_util_is_single_quote(*self->current_)){
    self->current_ = save;
    return false;
  }
  ng_ascii_util_advance_char(&self->current_, self->end_);
  
  // push token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->current_,
			   NG_NFA_FACTORY_TERMINAL);
  
  return true;
}


bool
ng_nfa_factory_tokenize_arrow(ng_nfa_factory_t* self)
{
  const char* save = self->current_;
  
  // consume -
  if(!ng_ascii_util_is_minus(*self->current_)){
    return false;
  }
  if(!ng_ascii_util_advance_char(&self->current_, self->end_)){
    self->current_ = save;
    return false;
  }
  
  // consume >
  if(!ng_ascii_util_is_gt(*self->current_)){
    self->current_ = save;
    return false;
  }
  ng_ascii_util_advance_char(&self->current_, self->end_);
  
  // push token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->current_,
			   NG_NFA_FACTORY_ARROW);
  
  return true;
}
