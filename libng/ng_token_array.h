#ifndef NG_TOKEN_ARRAY__H
#define NG_TOKEN_ARRAY__H


#ifdef __cplusplus
extern "C" {
#endif

  // forward declarations
  typedef struct ng_token ng_token_t;
  typedef struct ng_vector ng_vector_t;
  
  // holds an array of tokens e.g. the result of
  // some tokenization process
  typedef struct ng_token_array {
    ng_vector_t*    tokens_;    // array of tokens
    const char*     string_;    // string which has beeen tokenized.
  } ng_token_array_t;
  
  // construction
  ng_token_array_t* ng_token_array_new();
  ng_token_array_t* ng_token_array_init(ng_token_array_t* self);
  
  // destruction
  void ng_token_array_delete(ng_token_array_t** selfp);
  void ng_token_array_uninit(ng_token_array_t* self);
  
  // accesss

  void ng_token_array_set_string(ng_token_array_t* self,
				 const char* string);
  
  void ng_token_array_push_back(ng_token_array_t* self,
				const char* begin,
				const char* end,
				const long int type);

#ifdef __cplusplus
};
#endif

#endif  // end of include guard
