#ifndef NG_SYMBOL_TABLE_ENTRY__H
#define NG_SYMBOL_TABLE_ENTRY__H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_symbol_table_entry ng_symbol_table_entry_t;
  
  // debugging
  void ng_symbol_table_entry_dump(const ng_symbol_table_entry_t* self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard


