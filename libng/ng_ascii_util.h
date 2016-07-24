#ifndef NG_ASCII_UTIL__H
#define NG_ASCII_UTIL__H

// Ascii utilities.

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

  // single characters.  should be named by their
  // standard names
  bool ng_ascii_util_is_lower_case(const char);
  bool ng_ascii_util_is_upper_case(const char);
  bool ng_ascii_util_is_letter(const char);
  bool ng_ascii_util_is_digit(const char);
  bool ng_ascii_util_is_id(const char);
  bool ng_ascii_util_is_single_quote(const char ch);
  bool ng_ascii_util_is_double_quote(const char ch);
  bool ng_ascii_util_is_minus(const char);
  bool ng_ascii_util_is_gt(const char);
  bool ng_ascii_util_is_nl(const char);
  bool ng_ascii_util_is_cat_and_dog_sign(const char);
  bool ng_ascii_util_is_colon(const char);
  bool ng_ascii_util_is_forward_slash(const char);
  bool ng_ascii_util_is_backward_slash(const char);
  
  // (potentially) multi-character sequences
  bool ng_ascii_util_is_horizontal_white_space(const char);
  bool ng_ascii_util_is_white_space(const char);
  
  // utility function for advancing one char in a buffer.
  // only works for ascii chars, that's why its here :)
  bool ng_ascii_util_advance_char(const char**curr, const char*end);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
