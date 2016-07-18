#include<ng_token_array_entry.h>
#include<ng_token_array_entry.t.h>

#include<stdio.h>

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
