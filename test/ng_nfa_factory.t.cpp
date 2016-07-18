#include <gtest/gtest.h>


#include <ng_nfa_factory.h>
#include <ng_nfa_factory.t.h>

#include<stdbool.h>

const bool do_dump=true;


TEST(NgNfaFactoryTest, Alloc)
{
  ng_nfa_factory_t* factory = 0x0;
  factory = ng_nfa_factory_new();
  EXPECT_NE((ng_nfa_factory_t*)0x0, factory);
  
  
}
