#ifndef NG_SYMBOL_TABLE_T__H
#define NG_SYMBOL_TABLE_T__H

#include<stdlib.h>
#include<stdbool.h>

#include<ng_rb_tree.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  // forward declarations
  typedef struct ng_symbol_table ng_symbol_table_t;

  // debgugging
  void ng_symbol_table_dump(const ng_symbol_table_t* self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
