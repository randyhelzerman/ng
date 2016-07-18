#ifndef NG_SYMBOL_TABLE__H
#define NG_SYMBOL_TABLE__H

#include<stdlib.h>
#include<stdbool.h>

#include<ng_rb_tree.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  // forward declarations
  typedef struct ng_symbol_table_entry ng_symbol_table_entry_t;
  
  
  enum ng_symbol_table_errors {
    NG_SYMBOL_TABLE_WRONG_TYPE = 1
  };
  
  typedef struct ng_symbol_table {
    ng_rb_tree_t*   tree_;
  } ng_symbol_table_t;
  
  
  // constructor
  ng_symbol_table_t* ng_symbol_table_new();
  ng_symbol_table_t* ng_symbol_table_init();
  
  // destructor
  void ng_symbol_table_delete(ng_symbol_table_t** selfp);
  void ng_symbol_table_uninit(ng_symbol_table_t* self);
  
  // access
  int ng_symbol_table_insert(ng_symbol_table_t* self,
			     const char* name,
			     const int type);
  
  const ng_symbol_table_entry_t*
  ng_symbol_table_lookup(ng_symbol_table_t* self,
			 const char* name);
  
  // debgugging
  void ng_symbol_table_dump(const ng_symbol_table_t* self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
