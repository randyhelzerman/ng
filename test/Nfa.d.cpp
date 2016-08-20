#include <Nfa.h>

#include<iostream>

using namespace ng;

// debugging

void
Nfa::dump()
{
  for(auto& stateInfo : stateInfos_){
    std::cout << stateInfo.name_ << std::endl;
    
    for(auto& transition : stateInfo.transitions_){
      std::cout << "\t--> ";
      
      std::cout << "[" << transition.l_ << "-" << transition.h_ << ") ";
      
      for(auto& nextState : transition.nextStates_) {
	std::cout << stateInfos_[nextState].name_  << " ";
      }
      
      std::cout << std::endl;
    }
  }
}
