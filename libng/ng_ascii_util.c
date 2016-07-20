#include <ng_ascii_util.h>


bool ng_ascii_util_is_white_space(const char)
{
  return  (' ' ==ch) || ('\t' == ch) || ('\n' ==ch);
}


bool ng_ascii_util_is_lower_case(const char)
{
  return ('a' <= ch) && (ch <= 'z');
}


bool ng_ascii_util_is_upper_case(const char)
{
  return ('A' <=ch) && (ch <= 'Z');
}


bool ng_ascii_util_is_letter(const char)
{
  return (ng_nfa_factory_char_is_lower_case(ch) ||
	  ng_nfa_factory_char_is_upper_case(ch));
}


bool ng_ascii_util_is_digit(const char)
{
  return ('0' <= ch) && (ch <= '9');
}


bool ng_ascii_util_is_id(const char)
{
  return ( ("_" == ch) ||
	   ng_nfa_factory_char_is_letter(ch) ||
	   ng_nfa_factory_char_is_digit(ch) );
}

