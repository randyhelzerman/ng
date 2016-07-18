#include <gtest/gtest.h>

// module we are testing
#include <ng_nfa.h>
#include <ng_nfa.t.h>

// libraries
#include<stdio.h>

// supporting modules
#include <ng_vector.h>
#include <ng_interval.h>
#include <ng_nfa_state.h>

static const bool do_print = true;

TEST(NgNfaTest, AllocShort)
{
  // test alloc
  
  ng_nfa_t* nfa = 0x0;
  nfa = ng_nfa_new();
  EXPECT_NE(nfa, (ng_nfa_t*)0x0);
  EXPECT_NE(nfa->states_, (ng_vector_t*)0x0);
  
  // test de-alloc
  ng_nfa_delete(&nfa);
  EXPECT_EQ(nfa, (ng_nfa_t*)0x0);
}


TEST(NgNfaTest, AddArcs)
{
  // make an nfa
  ng_nfa_t* nfa = ng_nfa_new();
  
  // make a state
  ng_nfa_state_t* state = ng_nfa_state_new("A");
  
  // make some arcs to add to it
  ng_interval_t* arc1 = ng_interval_eq_new("a");
  ng_interval_push_color(arc1, 1,2);
  ng_nfa_state_add_interval(state,arc1);
  
  ng_interval_t* arc2 = ng_interval_eq_new("b");
  ng_interval_push_color(arc2, 3,4);
  ng_interval_push_color(arc2, 5,6);
  ng_nfa_state_add_interval(state,arc2);
  
  ng_interval_t* arc3 = ng_interval_gt_new("c");
  ng_interval_push_color(arc3, 7,8);
  ng_nfa_state_add_interval(state,arc3);
  
  // now add state to nfa
  ng_nfa_batch_add_state(nfa, state);
  ng_nfa_end_batch_add_state(nfa);
  
  if(do_print) ng_nfa_dump(nfa);
  
  // deallocate everything.  Test that the nfa
  // really has taken ownershp of the state's memory
  
  ng_nfa_delete(&nfa);
  
  // sadly, the state doesn't take ownership of the
  // interval, so  you still have to delete these
  // seperately.
  ng_interval_delete(&arc1);
  ng_interval_delete(&arc2);
  ng_interval_delete(&arc3);
}


// Ok, see if we can recognize a dorky little language
//
//  A -> "a"B
//  B -> "b"C
//  C -> "c"

// TEST(NgNfaTest, SmallTest)
// {
//   // make an nfa
//   ng_nfa_t* nfa = ng_nfa_new();
  
//   // beginning and ending arcs for every state
//   ng_interval_t* beg = ng_interval_eq_new("");
//   ng_interval_t* end = ng_interval_end_new();
  
//   // make a state for A
//   ng_nfa_state_t* state = ng_nfa_state_new("A");
//   ng_interval_t* arc1 = ng_interval_eq_new("a");

  
//   ng_nfa_state_t* state = ng_nfa_state_new("A");
  
// }
