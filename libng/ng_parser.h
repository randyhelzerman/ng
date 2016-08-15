#ifndef NG_PARSER__H
#define NG_PARSER__H

#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  // forward declarations
  typedef struct  ng_symbol_table  ng_symbol_table_t;
  typedef struct  ng_token_array_struct ng_token_array;
  
  
  enum NG_PARSER_TYPES {
    NG_PARSER_NON_TERMINAL,
    NG_PARSER_TERMINAL,
    NG_PARSER_BEGINNING_OF_INPUT,
    NG_PARSER_END_OF_INPUT,
    NG_PARSER_PROD,
    NG_PARSER_COMMENT,
    NG_PARSER_SENTENCE,
    NG_PARSER_PP,
    NG_PARSER_COLON,
    NG_PARSER_DIV,
    NG_PARSER_BSLASH,
    NG_PARSER_OPEN_PAREN,
    NG_PARSER_CLOSE_PAREN,
    NG_PARSER_CHARACTER_RANGE
  };
  
  // holds an array of tokens e.g. the result of
  // some tokenization process
  typedef struct ng_parser_struct {
    // hold lexical spec info
    ng_symbol_table_t*  symbol_table_;  // symbol table
    
    // related to tokenization
    ng_token_array*  tokens_;          // tokenized input
    const char* curr_;                 // current char being tokenized
    const char* end_;                  // end of the input string
  } ng_parser;
  
  // construction
  ng_parser* ng_parser_new();
  ng_parser* ng_parser_init(ng_parser* self);
  
  // deletion
  void ng_parser_delete(ng_parser** selfp);
  void ng_parser_uninit(ng_parser* selfp);
  
  // access
  
  // tokenize the tokens
  void ng_parser_tokenize(ng_parser* self,
			  const char* string);
  
  bool ng_parser_tokenize_horizontal_white_space(ng_parser* self);
  bool ng_parser_tokenize_non_terminal(ng_parser* self);
  bool ng_parser_tokenize_terminal(ng_parser* self);
  bool ng_parser_tokenize_PROD(ng_parser* self);
  bool ng_parser_tokenize_comment(ng_parser* self);
  bool ng_parser_tokenize_sentence(ng_parser* self);
  bool ng_parser_tokenize_PP(ng_parser* self);
  bool ng_parser_tokenize_COLON(ng_parser* self);
  bool ng_parser_tokenize_DIV(ng_parser* self);
  bool ng_parser_tokenize_BSLASH(ng_parser* self);
  bool ng_parser_tokenize_open_paren(ng_parser* self);
  bool ng_parser_tokenize_close_paren(ng_parser* self);
  bool ng_parser_tokenize_character_range(ng_parser* self);
  
  bool ng_parser_min_parse(ng_parser* self,
			   const char* in_string);
  
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
