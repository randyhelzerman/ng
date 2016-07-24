#ifndef NG_NFA_FACTORY__H
#define NG_NFA_FACTORY__H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  // forward declarations
  typedef struct  ng_symbol_table  ng_symbol_table_t;
  typedef struct  ng_token_array_struct   ng_token_array;
  typedef struct  ng_nfa           ng_nfa_t;
  
  enum NG_NFA_FACTORY_TYPES {
    NG_NFA_FACTORY_NON_TERMINAL,
    NG_NFA_FACTORY_TERMINAL,
    NG_NFA_FACTORY_END_OF_INPUT,
    NG_NFA_FACTORY_ARROW
  };
  
  
  typedef struct ng_nfa_factory {
    ng_token_array*     tokens_;        // tokenized input
    
    const char*         current_;       // points at current char being tokenized
    const char*         end_;           // points at end of string to be tokenized
    
    ng_symbol_table_t*  symbol_table_;  // symbol table
  } ng_nfa_factory_t;
  
  // construction
  ng_nfa_factory_t* ng_nfa_factory_new();
  ng_nfa_factory_t* ng_nfa_factory_init(ng_nfa_factory_t*);
  
  // deletion
  void ng_nfa_factory_delete(ng_nfa_factory_t** selfp);
  void ng_nfa_factory_uninit(ng_nfa_factory_t* self);
  
  // access
  
  // build an nfa from parsing the string spec
  // caller takes over ownership of memory allocted
  // for the nfa
  ng_nfa_t* ng_nfa_factory_build(ng_nfa_factory_t* self,
				 const char* string);
  
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
