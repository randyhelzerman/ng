#include <ng_ascii_util.h>


bool ng_ascii_util_is_white_space(const char ch)
{
  return  (' ' ==ch) || ('\t' == ch) || ('\n' ==ch);
}


bool ng_ascii_util_is_lower_case(const char ch)
{
  return ('a' <= ch) && (ch <= 'z');
}


bool ng_ascii_util_is_upper_case(const char ch)
{
  return ('A' <=ch) && (ch <= 'Z');
}


bool ng_ascii_util_is_letter(const char ch)
{
  return (ng_ascii_util_is_lower_case(ch) ||
	  ng_ascii_util_is_upper_case(ch));
}


bool ng_ascii_util_is_digit(const char ch)
{
  return ('0' <= ch) && (ch <= '9');
}


bool ng_ascii_util_is_id(const char ch)
{
  return (('_' == ch) ||
	  ng_ascii_util_is_letter(ch) ||
	  ng_ascii_util_is_digit(ch));
}


bool ng_ascii_util_is_single_quote(const char ch)
{
  return '\'' == ch;
}


bool
ng_ascii_util_is_double_quote(const char ch)
{
  return '"' == ch;
}


bool ng_ascii_util_is_minus(const char ch)
{
  return '-' == ch;
}


bool ng_ascii_util_is_gt(const char ch)
{
  return '>' == ch;
}
    
  
bool
ng_ascii_util_advance_char(const char**curr,
			   const char*end)
{
  (*curr)++;
  if(*curr == end) return false;
  
  return true;
}
