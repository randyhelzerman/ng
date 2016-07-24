#ifndef NG_TOKEN__H
#define NG_TOKEN__H


#ifdef __cplusplus
extern "C" {
#endif
  
  
  // holds an array of tokens e.g. the result of
  // some tokenization process
  typedef struct ng_token_struct {
    const char*       begin_;        // Beginning of token chars
    const char*       end_;          // One past ending of token chars
    long int          type_;         // type of token this is
    char              airity_;       // how many arguments it takes
  } ng_token;
  
  
  // construction
  ng_token*
  ng_token_new(const char* begin,
	       const char* end,
	       const long int type);
  
  ng_token*
  ng_token_init(ng_token* self,
		const char* begin,
		const char* end,
		const long int type);
  
  // destruction
  void ng_token_delete(ng_token** selfp);
  void ng_token_uninit(ng_token* self);
  
  //-------
  // access
  //-------
  
  int
  ng_token_strlen(const ng_token* self);
  
  void
  ng_token_cp_to_buf(const ng_token* self,
		     char* buf,
		     const int max);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
