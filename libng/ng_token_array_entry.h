#ifndef NG_TOKEN_ARRAY_ENTRY__H
#define NG_TOKEN_ARRAY_ENTRY__H


#ifdef __cplusplus
extern "C" {
#endif
  
  
  // holds an array of tokens e.g. the result of
  // some tokenization process
  typedef struct ng_token_array_entry {
    const char*       begin_;        // Beginning of token chars
    const char*       end_;          // One past ending of token chars
    long int          type_;         // type of token this is
  } ng_token_array_entry_t;
  
  
  // construction
  ng_token_array_entry_t*
  ng_token_array_entry_new(const char* begin,
			   const char* end,
			   const long int type);
  
  ng_token_array_entry_t*
  ng_token_array_entry_init(ng_token_array_entry_t* self,
			    const char* begin,
			    const char* end,
			    const long int type);
  
  // destruction
  void ng_token_array_entry_delete(ng_token_array_entry_t** selfp);
  void ng_token_array_entry_uninit(ng_token_array_entry_t* self);
  
  //-------
  // access
  //-------
  
  int ng_token_array_entry_strlen(const ng_token_array_entry_t* self);
  
  void
  ng_token_array_entry_cp_to_buf(const ng_token_array_entry_t* self,
				 char* buf,
				 const int max);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
