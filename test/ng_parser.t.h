#ifndef NG_PARSER_T__H
#define NG_PARSER_T__H

#include<stdlib.h>
#include<stdbool.h>

// forward declarations
typedef struct ng_parser_struct ng_parser;

#ifdef __cplusplus
extern "C" {
#endif
  void ng_parser_dump(ng_parser *self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
