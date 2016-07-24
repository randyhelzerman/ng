#include <gtest/gtest.h>

#include <stdbool.h>
const bool do_print = true;


#include <ng_util_io.h>


TEST(NGUTILIO, SimpleRead)
{
  // get the stuffs
  char* buf=0x0;
  loadFileIntoBuffer("../test/ng.ng", &buf);
  EXPECT_NE((char*)0x0, buf);
  
  if(do_print) printf("%s", buf);
  
  free(buf);
}


TEST(NGUTILIO, Nofile)
{
  // get the stuffs
  char* buf = (char*)0x0deadbeef;
  loadFileIntoBuffer("../test/flabbberblather", &buf);
  EXPECT_EQ((char*)0x0, buf);
}
