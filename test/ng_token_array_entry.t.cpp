#include <gtest/gtest.h>

#include <ng_token_array_entry.h>

#include<stdbool.h>

const bool do_print = false;

TEST(NgTokenArrayEntryTest, Alloc0)
{
  //                  0123456789012345678901234567890
  const char* bluf = "A -> 'a'B   B->'b'C   C->'c'";
  
  // create some entries to represent tokens in the above string
  
  // "A"
  ng_token_array_entry_t* t0 = ng_token_array_entry_new(bluf+0,bluf+1, 10);
  char bluf0[100];
  ng_token_array_entry_cp_to_buf(t0, bluf0, 100);
  EXPECT_EQ(0, strcmp(bluf0, "A"));
  
  // "->"
  ng_token_array_entry_t* t1 = ng_token_array_entry_new(bluf+2,bluf+4, 11);
  char bluf1[100];
  ng_token_array_entry_cp_to_buf(t1, bluf1, 100);
  EXPECT_EQ(0, strcmp(bluf1, "->"));
  
  // 'a'
  ng_token_array_entry_t* t2 = ng_token_array_entry_new(bluf+5, bluf+8, 12);
  char bluf2[100];
  ng_token_array_entry_cp_to_buf(t2, bluf2,100);
  EXPECT_EQ(0, strcmp(bluf2, "'a'"));
  
  if (do_print) ng_token_array_entry_dump(t0);
  if (do_print) ng_token_array_entry_dump(t1);
  if (do_print) ng_token_array_entry_dump(t2);
  
  ng_token_array_entry_delete(&t0);
  ng_token_array_entry_delete(&t1);
  ng_token_array_entry_delete(&t2);
}
