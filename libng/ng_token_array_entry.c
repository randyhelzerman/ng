#include <ng_token_array_entry.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// construction
ng_token_array_entry_t*
ng_token_array_entry_new(const char* begin,
			 const char* end,
			 const long int type)
{
  ng_token_array_entry_t*  self
    = (ng_token_array_entry_t*)malloc(sizeof(ng_token_array_entry_t));

  return ng_token_array_entry_init(self, begin, end, type);
}

  
ng_token_array_entry_t*
ng_token_array_entry_init(ng_token_array_entry_t* self,
			  const char* begin,
			  const char* end,
			  const long int type)
{
  self->begin_ = begin;
  self->end_   = end;
  self->type_  = type;
  
  return self;
}
  

// destruction
void ng_token_array_entry_delete(ng_token_array_entry_t** selfp)
{
  ng_token_array_entry_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_token_array_entry_uninit(ng_token_array_entry_t* self)
{
  self->begin_ = 0x0;
  self->end_ = 0x0;
}
  

//-------
// access
//-------


int ng_token_array_entry_strlen(const ng_token_array_entry_t* self)
{
  // The number of chars in the range, plus 1 for the 0x0 terminator
  return 1 + (self->end_ - self->begin_);
}


void
ng_token_array_entry_cp_to_buf(const ng_token_array_entry_t* self,
			       char* buf,
			       const int max)
{
  // figure the max length we can print
  const int n1 = ng_token_array_entry_strlen(self);
  const int n = (n1>max) ? max : n1;
  
  // print out token name to bufer
  snprintf(buf, n, "%s", self->begin_);
}


void ng_token_array_entry_dump(const ng_token_array_entry_t* self)
{
  // make a buffer to hold the token name
  char bluf[100];
  
  ng_token_array_entry_cp_to_buf(self, bluf, 100);
  
  // print token entry to stdout
  printf("%10s : type=%03ld\n", bluf, self->type_);
}  
