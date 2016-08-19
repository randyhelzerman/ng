#ifndef NGPP_NFA__H
#define NGPP_NFA__H

#include <vector>
#include <string>

namespace ng {
  
  class Nfa {
    // builds this
    friend class Parser;
    
    // hold info for arc between state(s)(es)
    struct Transition {
      std::string l_;
      std::string h_;
      std::vector<int> nextStates_;
      
      Transition(const std::string& l,
		 const std::string& h)
      : l_(l), h_(h) {}
    };
    
    
    // holds info for each state
    struct StateInfo {
      std::string name_;
      std::vector<Transition> transitions_;
      
      StateInfo(const std::string& name) : name_(name) {}
    };
    
    
    // functions to construct -- called by parser
    const int addState(const std::string& name);
    
    const int addTransition(const int state,
			    const std::string& l,
			    const std::string& h);
    
    
    void addNextStateToTransition(const int state,
				  const int transition,
				  const int nextState);
    
    
    // holds state
    std::vector<StateInfo> stateInfos_;
    
  public:
    
    // ctor
    Nfa(){}
    
    // debugging
    void dump();
  };
  
};

#endif

