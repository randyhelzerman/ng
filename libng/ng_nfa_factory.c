#include <ng_nfa_factory.h>

#include <ng_token_array.h>
#include <ng_symbol_table.h>

#include <stdlib.h>

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
ng_nfa_t* build(ng_nfa_factory_t* self,
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
void ng_nfa_factory_tokenize(ng_nfa_factory_t* self)
{
  self->current_ = self->tokens_->string_;
  
  ng_nfa_factory_tokenize_white_space(self);
  ng_nfa_factory_tokenize_non_terminal(self);
}


// always returns true.  Just consumes whitespace
bool ng_nfa_factory_tokenize_white_space(ng_nfa_factory_t* self)
{
  while(*self->current_ != ' ' || *self->current_ != '\t' || *self->current_ != '\n'){
    self->current_++;
    if(self->current_ == self->end_) return true;
  }
  
  return true;
}


// returns true if we can tokenize a non-terminal.
bool ng_nfa_factory_tokenize_non_terminal(ng_nfa_factory_t* self)
{
  const char* save = self->current_;
  
  while((*self->current_ >= 'a' && *self->current_ <= 'z')
	||
	(*self->current_ >= 'A' && *self->current_ <= 'Z')
	||
	(*self->current_ >= '0' && *self->current_ <= '9')){
    self->current_++;
    if(self->current_ == self->end_) break;
  }
  
  // if we haven't found a non-terminal, return false
  if(save == self->current_) return false;
  
  // push a non-terminal token on the stack if we've found one
  ng_token_array_push_back(self->tokens_,save, self->current_, NG_NFA_FACTORY_NON_TERMINAL);
  return true;
}


bool ng_nfa_factory_tokenize_terminal(ng_nfa_factory_t* self)
{
  // must start with a '
  if(*self->current_ != '\'') return false;
  
  const char* save = self->current_;
  self->current_++;
  
  // ensure we haven't fallen off the edge
  if(self->current_ == self->end_){
    self->current_ = save;
    return false;
  }
  
  while((*self->current_ >= 'a' && *self->current_ <= 'z')
	||
	(*self->current_ >= 'A' && *self->current_ <= 'Z')
	||
	(*self->current_ >= '0' && *self->current_ <= '9')){
    self->current_++;
    
    // need to find closing '
    if(self->current_ == self->end_) {
      self->current_ = save;
      return false;
    }
  }
  
  if(*self->current_ == '\''){
    self->current_++;
  } else {
    self->current_ = save;
    return false;
  }
  
  // if we haven't found a non-terminal, return false
  if(save == self->current_) return false;
  
  // push a non-terminal token on the stack if we've found one
  ng_token_array_push_back(self->tokens_,save, self->current_, NG_NFA_FACTORY_TERMINAL);
  return true;
}



