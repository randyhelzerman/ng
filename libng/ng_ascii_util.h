#ifndef NG_ASCII_UTIL__H
#define NG_ASCII_UTIL__H

// Ascii utilities.

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  bool ng_ascii_util_is_white_space(const char);
  bool ng_ascii_util_is_lower_case(const char);
  bool ng_ascii_util_is_upper_case(const char);
  bool ng_ascii_util_is_letter(const char);
  bool ng_ascii_util_is_digit(const char);
  bool ng_ascii_util_is_id(const char);
  
  bool ng_ascii_util_advance_char(const char**curr, const char*end);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
