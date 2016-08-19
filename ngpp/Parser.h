#ifndef NGPP_PARSER__H
#define NGPP_PARSER__H

#include <string>
#include <vector>
#include <unordered_map>


namespace ng {
  
  // forward declarations
  class Nfa;
  
  class Parser {
    
    struct StateInfo {
      
      struct Transition {
	// closed interval
	std::string l_;
	std::string h_;
	
	// where to go next.
	// 
	const int nextState_;
	
        Transition(const std::string& l,
		   const std::string& h,
		   // defaults to stop state
		   const int nextState = 0)
	: l_(l), h_(h), nextState_(nextState) {}
      };
	
      std::string name_;
      std::vector<Transition> transitions_;
      
      StateInfo(const std::string name) : name_(name) {}
      
    };
    
    int nonTerminalCount_;
    std::unordered_map<std::string,int> nonTerminals_;
    
    std::vector<StateInfo> stateInfos_;
    
    void initParsing_();
    void addNonTerminal_(const std::string& name);
    
    void addTransition_(const std::string& head,
			const std::string& l,
			const std::string& h,
			const std::string& nextState);
    
    void buildState(Nfa& nfa,
		    const StateInfo& stateInfo);
    
  public:
    
    void parse(const std::string filename);
    
    void build(Nfa& nfa);
    
    // debugging
    
    void dump();
    
  };
  
  
};
    

#endif

