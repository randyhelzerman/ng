#ifndef NG_SYMBOL_TABLE_ENTRY__H
#define NG_SYMBOL_TABLE_ENTRY__H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_symbol_table_entry {
    long int   type_;      //  The type this symbol is
    int        id_;        //  integer id for this
    char       name_[];    //  name thereof
  } ng_symbol_table_entry_t;
  
  
  // construction
  ng_symbol_table_entry_t *
  ng_symbol_table_entry_new(const char* name,
			    long int type);
  
  ng_symbol_table_entry_t *
  ng_symbol_table_entry_init(ng_symbol_table_entry_t*self,
			     const char* name,
			     long int type);
  
  ng_symbol_table_entry_t*
  ng_symbol_table_entry_cp_init(const ng_symbol_table_entry_t* src,
				ng_symbol_table_entry_t* tgt);
  
  // destruction
  void ng_symbol_table_entry_delete(ng_symbol_table_entry_t **selfp);
  void ng_symbol_table_entry_uninit(ng_symbol_table_entry_t* self);
  
  // access
  size_t ng_symbol_table_entry_size(const ng_symbol_table_entry_t* self);
  
  int ng_symbol_table_entry_compare(const ng_symbol_table_entry_t* e1,
				    const ng_symbol_table_entry_t* e2);

  // returns true if the two entries are equal.  Note this doesn't
  // have to be the same conditions under which the comparison
  // function above returns zero, because we can be using this
  // as a map.
  bool ng_symbol_table_entry_equal(const ng_symbol_table_entry_t* e1,
				   const ng_symbol_table_entry_t* e2);

  // debugging
  void ng_symbol_table_entry_dump(const ng_symbol_table_entry_t* self);
  

#ifdef __cplusplus
};
#endif

#endif  // end of include guard

  
    
