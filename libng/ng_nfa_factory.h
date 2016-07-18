#ifndef NG_NFA_FACTORY__H
#define NG_NFA_FACTORY__H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  // forward declarations
  typedef ng_symbol_table ng_symbol_table_t;
  typedef ng_token_array ng_token_array_t;
  typedef ng_nfa ng_nfa_t;
  
  enum NG_NFA_FACTORY_TYPES {
    NG_NFA_FACTORY_NON_TERMINAL,
    NG_NFA_FACTORY_TERMINAL,
    NG_NFA_FACTORY_END_OF_INPUT,
  };
  
  
  typedef struct ng_nfa_factory {
    ng_token_array_t*    tokens_         // tokenized input
    ng_symbol_table_t*   symbol_table_;  // symbol table
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
  ng_nfa_t* build(const char* string);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
