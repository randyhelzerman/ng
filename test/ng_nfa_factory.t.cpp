#include <gtest/gtest.h>


#include <ng_nfa_factory.h>
#include <ng_nfa_factory.t.h>

#include<stdbool.h>

const bool do_dump=false;


TEST(NgNfaFactoryTest, Alloc)
{
  // allocate a factory
  ng_nfa_factory_t* factory = 0x0;
  factory = ng_nfa_factory_new();
  EXPECT_NE((ng_nfa_factory_t*)0x0, factory);
  
  // 
  ng_nfa_factory_delete(&factory);
  EXPECT_EQ((ng_nfa_factory_t*)0x0, factory);
}


TEST(NgNfaFactoryTest, tokenizersP)
{
  ng_nfa_factory_t* factory = ng_nfa_factory_new();
  if (do_dump) ng_nfa_factory_dump(factory);
  ng_nfa_factory_delete(&factory);
}
