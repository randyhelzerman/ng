#ifndef NG_TOKEN_T__H
#define NG_TOKEN_T__H

// forward declarations
typedef struct ng_token ng_token_t;

#ifdef __cplusplus
extern "C" {
#endif
  
  void ng_token_dump(const ng_token_t* self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
