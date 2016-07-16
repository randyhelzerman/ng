#include <gtest/gtest.h>


#include <ng_interval.h>
#include <ng_nfa_state.h>

static const bool do_print = false;


TEST(NgNfaStateTest, AllocShort)
{
  // test alloc
  ng_nfa_state_t* state = ng_nfa_state_new("A");
  EXPECT_NE(state,          (ng_nfa_state_t*)0x0);
  EXPECT_NE(state->arcs_,   (ng_vector_t*)(0x0));
  EXPECT_EQ(state->action_, (void*)0x0);
  
  if(do_print) ng_nfa_state_dump(state,0);
  
  // test de-alloc
  ng_nfa_state_delete(&state);
  EXPECT_EQ(state, (ng_nfa_state_t*)0x0);
}


TEST(NgNfaStateTest, AddArcs)
{
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
  
  if(do_print) ng_nfa_state_dump(state,0);
  
  // deallocate everything
  ng_interval_delete(&arc1);
  ng_interval_delete(&arc2);
  ng_interval_delete(&arc3);
  
  ng_nfa_state_delete(&state);
}


TEST(NgNfaStateTest, Compare)
{
  // make a state
  ng_nfa_state_t* state1 = ng_nfa_state_new("A");
  ng_nfa_state_t* state2 = ng_nfa_state_new("ABC");
  ng_nfa_state_t* state3 = ng_nfa_state_new("C");
  ng_nfa_state_t* state4 = ng_nfa_state_new("C");
  
  EXPECT_GT(0, ng_nfa_state_compare(state1, state2));
  EXPECT_LT(0, ng_nfa_state_compare(state3, state1));
  EXPECT_EQ(0, ng_nfa_state_compare(state3, state4));
  
  // deallocate everything
  ng_nfa_state_delete(&state1);
  ng_nfa_state_delete(&state2);
  ng_nfa_state_delete(&state3);
  ng_nfa_state_delete(&state4);
}
