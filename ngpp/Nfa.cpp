#include <Nfa.h>

using namespace ng;

// functions to construct -- called by parser
const int
Nfa::addState(const std::string& name)
{
  stateInfos_.push_back(StateInfo(name));
  return stateInfos_.size()-1;
}


const int
Nfa::addTransition(const int state,
		   const std::string& l,
		   const std::string& h)
{
  stateInfos_[state].transitions_.push_back(Transition(l,h));
  return stateInfos_[state].transitions_.size()-1;
}


void
Nfa::addNextStateToTransition(const int state,
			      const int transition,
			      const int nextState)
{  stateInfos_[state]
    .transitions_[transition]
    .nextStates_
    .push_back(nextState);
}
