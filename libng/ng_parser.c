#include <ng_parser.h>

#include <stdlib.h>
#include <string.h>

#include <ng_ascii_util.h>
#include <ng_token_array.h>
#include <ng_symbol_table.h>
#include <ng_symbol_table_entry.h>


// construction
ng_parser* ng_parser_new()
{
  // allocate sufficient memory
  ng_parser* self
    = (ng_parser*)malloc(sizeof(ng_parser));
  
  // initialize it
  return ng_parser_init(self);
}


ng_parser* ng_parser_init(ng_parser* self)
{
  self->tokens_ = 0x0;
  self->symbol_table_ = ng_symbol_table_new();
  
  return self;
}


// deletion
void ng_parser_delete(ng_parser** selfp)
{
  ng_parser_uninit(*selfp);
  free(*selfp);
  
  *selfp = 0x0;
}


void ng_parser_uninit(ng_parser* self)
{
  // delete tokenizing stuffs
  ng_token_array_delete(&self->tokens_);
  self->curr_ = 0x0;
  self->end_  = 0x0;
  
  // delete parsing stuffs
  ng_symbol_table_delete(&self->symbol_table_);
}

  
// access

// tokenize the tokens
void ng_parser_tokenize(ng_parser* self,
			const char* string)
{
  // refresh the tokens stuffs
  ng_token_array_delete(&self->tokens_);
  self->tokens_ = ng_token_array_new();
  self->tokens_->string_ = string;
  
  self->curr_ = self->tokens_->string_;
  self->end_ = self->tokens_->string_ + strlen(self->tokens_->string_);
  
  bool gogo = true;
  while(gogo){
    ng_parser_tokenize_horizontal_white_space(self);
    
    gogo = (ng_parser_tokenize_non_terminal(self)
	    ||
	    ng_parser_tokenize_terminal(self)
	    ||
	    ng_parser_tokenize_PROD(self)
	    ||
	    ng_parser_tokenize_comment(self)
	    ||
	    ng_parser_tokenize_COLON(self)
	    ||
	    ng_parser_tokenize_sentence(self)
	    ||
	    ng_parser_tokenize_PP(self)
	    ||
	    ng_parser_tokenize_DIV(self)
	    ||
	    ng_parser_tokenize_BSLASH(self)
	    ||
	    ng_parser_tokenize_open_paren(self)
	    ||
	    ng_parser_tokenize_close_paren(self)
	    )
      && self->curr_ < self->end_;
  }
}


bool
ng_parser_tokenize_horizontal_white_space(ng_parser* self)
{
  while(ng_ascii_util_is_horizontal_white_space(*self->curr_)){
    if(!ng_ascii_util_advance_char(&self->curr_,
				   self->end_))
      return true;
  }
  
  return true;
}


bool ng_parser_tokenize_non_terminal(ng_parser* self)
{
  const char* save = self->curr_;
  
  // needs at least one letter to strt
  if(!ng_ascii_util_is_letter(*self->curr_)){
    return false;
  }
  
  // advance
  if(!ng_ascii_util_advance_char(&self->curr_, self->end_)){
    // push the token
    ng_token_array_push_back(self->tokens_,
			     save, self->curr_,
			     NG_PARSER_NON_TERMINAL);
    return true;
  }
  
  while(ng_ascii_util_is_id(*self->curr_)){
    if(!ng_ascii_util_advance_char(&self->curr_, self->end_)){
      // push the token
      ng_token_array_push_back(self->tokens_,
			       save, self->curr_,
			       NG_PARSER_NON_TERMINAL);
      return true;
    }
  }
  
  // push the last token
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_NON_TERMINAL);
  return true;
}


bool ng_parser_tokenize_terminal(ng_parser* self)
{
  // cache the beginning 
  const char* save = self->curr_;
  
  // consume first quote
  if(!ng_ascii_util_is_single_quote(*self->curr_)){
    return false;
  }
  
  // if we've run out of string, restore position and return false
  if(!ng_ascii_util_advance_char(&self->curr_, self->end_)){
    self->curr_ = save;
    return false;
  }
  
  // consume name
  while(!ng_ascii_util_is_single_quote(*self->curr_)){
    // if we've run out of string, restore position and return false
    if(!ng_ascii_util_advance_char(&self->curr_, self->end_)){
      self->curr_ = save;
      return false;
    }
  }
  
  // consume final quote
  // consume first quote
  if(!ng_ascii_util_is_single_quote(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  ng_ascii_util_advance_char(&self->curr_, self->end_);
  
  // push token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_TERMINAL);
  
  return true;
}


bool ng_parser_tokenize_PROD(ng_parser* self)
{
  const char* save = self->curr_;
  
  // consume -
  if(!ng_ascii_util_is_minus(*self->curr_)){
    return false;
  }
  if(!ng_ascii_util_advance_char(&self->curr_, self->end_)){
    self->curr_ = save;
    return false;
  }
  
  // consome the other -
  if(!ng_ascii_util_is_minus(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  if(!ng_ascii_util_advance_char(&self->curr_, self->end_)){
    self->curr_ = save;
    return false;
  }
  
  // consume >
  if(!ng_ascii_util_is_gt(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  ng_ascii_util_advance_char(&self->curr_, self->end_);
  
  // push token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_PROD);
  
  return true;
}


bool
ng_parser_tokenize_comment(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_cat_and_dog_sign(*self->curr_)){
    return false;
  }
  
  while((self->end_ != self->curr_)
	&&
	! ng_ascii_util_is_nl(*self->curr_)){
    self->curr_++;
  }
  
  // note: leave curr_ pointing at the \n
  // because we want that to be considered
  // either whitespace or a paragraph break
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_COMMENT);
  
  return true;
}


bool ng_parser_tokenize_sentence(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_nl(*self->curr_)) return false;
  self->curr_++;
  
  // two newlines back to back are a paragraph seperator
  if((self->end_ != self->curr_) && ng_ascii_util_is_nl(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_SENTENCE);
  
  return true;
}


// paragraph break
bool
ng_parser_tokenize_PP(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_nl(*self->curr_)) return false;
  if(!ng_ascii_util_advance_char(&self->curr_,self->end_)){
    self->curr_ = save;
    return false;
  }
  
  if(!ng_ascii_util_is_nl(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  
  self->curr_++;
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_PP);
  
  return true;
}


bool
ng_parser_tokenize_COLON(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_colon(*self->curr_)){
    return false;
  }
  self->curr_++;
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_COLON);
  
  return true;
}


bool
ng_parser_tokenize_DIV(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_forward_slash(*self->curr_)){
    return false;
  }

  // two forward slashses is a different operator
  if(ng_ascii_util_advance_char(&self->curr_,self->end_)
     &&
     ng_ascii_util_is_forward_slash(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_DIV);
  
  return true;
}


bool
ng_parser_tokenize_BSLASH(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_backward_slash(*self->curr_)){
    return false;
  }
  
  // two forward slashses is a different operator
  if(ng_ascii_util_advance_char(&self->curr_,self->end_)
     &&
     ng_ascii_util_is_backward_slash(*self->curr_)){
    self->curr_ = save;
    return false;
  }
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_BSLASH);
  
  return true;
}


bool ng_parser_tokenize_open_paren(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_open_paren(*self->curr_)){
    return false;
  }
  self->curr_++;
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_OPEN_PAREN);
  
  return true;
}


bool ng_parser_tokenize_close_paren(ng_parser* self)
{
  const char* save = self->curr_;
  
  if(!ng_ascii_util_is_close_paren(*self->curr_)){
    return false;
  }
  self->curr_++;
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_CLOSE_PAREN);
  
  return true;
}


bool
ng_parser_tokenize_character_range(ng_parser* self)
{
  const char* save = self->curr_;
  
  // consume opening square bracket
  if(!ng_ascii_util_is_open_square_bracket(*self->curr_)){
    return false;
  }
  if(!ng_ascii_util_advance_char(&self->curr_,self->end_)){
    self->curr_ = save;
    return false;
  }
  
  while(!ng_ascii_util_is_close_square_bracket(*self->curr_)){
    if(!ng_ascii_util_advance_char(&self->curr_,self->end_)){
      self->curr_ = save;
      return false;
    }
  }
  
  // consume closing brace
  ng_ascii_util_advance_char(&self->curr_,self->end_);
  
  // push the token we just recognized
  ng_token_array_push_back(self->tokens_,
			   save, self->curr_,
			   NG_PARSER_CHARACTER_RANGE);
  
  return true;
}


bool
ng_parser_min_parse(ng_parser* self,
		    const char* in_string)
{
  // init parser state
  self->tokens_ = 0x0;
  
  // we want to be able to parse read only strings
  // so we'll have top copy this
  char* input = strdup(in_string);
  
  char* p = input;
  
  char* token = 0x0;
  while((token = strtok(p, " \n\t"))){
    p = 0x0;
    // insert non terminal--we know its there.
    ng_symbol_table_insert(self->symbol_table_,
			   token, NG_PARSER_NON_TERMINAL);
    
    // eat the production symbol
    if(!(token = strtok(p, " \n\t"))){
      // we were expecting '-->'
      free(input);
      return false;
    }
    
    // read the range
    
    // read lower bound
    if(!(token=strtok(p, " \n\t[-"))){
      free(input);
      return false;
    }
    
    // get lower bound
    if(!(token=strtok(p, " \n\t]-"))){
      free(input);
      return false;
    }
    
    // see if there is a final nonterminal
    if((token=strtok(p, " \n\t"))){
      ng_symbol_table_insert(self->symbol_table_,
			     token, NG_PARSER_NON_TERMINAL);
    }
  }
  
  // free the duplicated input
  free(input);

  return true;
}


const ng_symbol_table_entry_t*
ng_parser_get_symbol_table_entry(ng_parser*  self,
				 const char* name,
				 const int   type)
{
  // first see if it is already there
  const ng_symbol_table_entry_t* returner
    = ng_symbol_table_lookup((void*)self, name, type);
  
  if(0x0==returner){
    returner = ng_symbol_table_insert(self->symbol_table_, name, type);
    ((ng_symbol_table_entry_t*)(returner))->id_ = self->symbol_id_numb;
    self->symbol_id_numb++;
  }
  
  return returner;
}


