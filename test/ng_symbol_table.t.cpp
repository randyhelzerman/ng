#include <gtest/gtest.h>

// module being tested
#include<ng_parser.h>
#include<ng_symbol_table.h>
#include<ng_symbol_table.t.h>
#include<ng_symbol_table_entry.h>
#include<ng_symbol_table_entry.t.h>

#include<stdbool.h>

const bool do_print= false;

TEST(NgSymbolTableTest, Alloc)
{
  ng_symbol_table_t* symbol_table = 0x0;
  symbol_table = ng_symbol_table_new();
  EXPECT_NE(symbol_table, (ng_symbol_table_t*)0x0);
  
  ng_symbol_table_delete(&symbol_table);
  EXPECT_EQ((ng_symbol_table_t*)0x0, symbol_table);
}


TEST(NgSymbolTableTest, TestInsertLookup)
{
  ng_symbol_table_t* symbol_table = ng_symbol_table_new();
  
  // test that we can insert a new symbol ok.
  if(ng_symbol_table_insert(symbol_table,
			    "foo",
			    NG_PARSER_NON_TERMINAL)){
    EXPECT_EQ(1,1);
  } else {
    EXPECT_EQ(1,0);
  }
  
  // test that we can look it back up again
  {
    const ng_symbol_table_entry_t* entry
      = ng_symbol_table_lookup(symbol_table,
			       "foo",
			       NG_PARSER_NON_TERMINAL);
    EXPECT_EQ(0, strcmp("foo", entry->name_));
    EXPECT_EQ(NG_PARSER_NON_TERMINAL, entry->type_);
  }
  
  // test that we can enter identical entries more than once
  if(ng_symbol_table_insert(symbol_table, "foo", NG_PARSER_NON_TERMINAL)){
    EXPECT_EQ(1,1);
  } else {
    EXPECT_EQ(1,0);
  }
  
  {
    const ng_symbol_table_entry_t* entry
      = ng_symbol_table_lookup(symbol_table,
			       "foo",
			       NG_PARSER_NON_TERMINAL);
    EXPECT_EQ(0, strcmp("foo", entry->name_));
    EXPECT_EQ(NG_PARSER_NON_TERMINAL, entry->type_);
  }
  
  // test we can do another one with different type
  if(ng_symbol_table_insert(symbol_table, "bar", NG_PARSER_NON_TERMINAL)){
    EXPECT_EQ(1,1);
  } else {
    EXPECT_EQ(1,0);
  }
  {
    const ng_symbol_table_entry_t* entry
      = ng_symbol_table_lookup(symbol_table, "bar",
			       NG_PARSER_NON_TERMINAL);
    
    EXPECT_EQ(0, strcmp("bar", entry->name_));
    EXPECT_EQ(NG_PARSER_NON_TERMINAL, entry->type_);
  }
  
  if (do_print) ng_symbol_table_dump(symbol_table);
  
  const ng_symbol_table_entry_t* entry
    = ng_symbol_table_lookup(symbol_table, "foo",
			     NG_PARSER_NON_TERMINAL);
  
  ng_symbol_table_delete(&symbol_table);
}


