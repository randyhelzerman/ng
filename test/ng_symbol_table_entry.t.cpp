#include <gtest/gtest.h>

// module being tested
#include <ng_symbol_table_entry.h>


TEST(NgSymbolTableEntryTest, Alloc)
{
  ng_symbol_table_entry_t* entry = ng_symbol_table_entry_new("N",2);
  EXPECT_NE((ng_symbol_table_entry_t*)(0x0), entry);
  
  EXPECT_EQ(entry->type_,   2);
  EXPECT_EQ(entry->id_,     0);
  EXPECT_EQ(0, strcmp("N",  entry->name_));
  
  ng_symbol_table_entry_delete(&entry);
  EXPECT_EQ((ng_symbol_table_entry_t*)(0x0), entry);
}


TEST(NgSymbolTableEntryTest, Compare)
{
  ng_symbol_table_entry_t* entry1 = ng_symbol_table_entry_new("foo",2);
  ng_symbol_table_entry_t* entry2 = ng_symbol_table_entry_new("bar",2);
  
  EXPECT_LT(0, ng_symbol_table_entry_compare(entry1,entry2));
  
  ng_symbol_table_entry_delete(&entry1);
  ng_symbol_table_entry_delete(&entry2);
}

