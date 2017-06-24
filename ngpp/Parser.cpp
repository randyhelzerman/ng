#include <Parser.h>

using namespace std;
using namespace ng;

#include <set>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <Nfa.h>

void
Parser::initParsing_()
{
  nonTerminalCount_ = 0;
  nonTerminals_.clear();
  
  // add stop state
  addNonTerminal_("");
}


void
Parser::addNonTerminal_(const std::string& name)
{
  // first see if this nonterminal has already been added.
  if(nonTerminals_.end() != nonTerminals_.find(name)){
    return;
  }
  
  // Add the new nonterminal
  nonTerminals_[name] = nonTerminalCount_;

  // push a new one on the end of states
  stateInfos_.push_back(StateInfo(name));
  
  // bump the count
  nonTerminalCount_++;
}


void
Parser::addTransition_(const std::string& head,
		       const std::string& l,
		       const std::string& h,
		       const std::string& nextState)
{
  const int headIndex = nonTerminals_[head];
  const int nextIndex = nonTerminals_[nextState];
  stateInfos_[headIndex]
    .transitions_
    .push_back(StateInfo::Transition(l,h,nextIndex));
}


void
Parser::parse(const std::string filename)
{
  initParsing_();
  
  std::ifstream infile(filename);
  
  std::string line;
  while (std::getline(infile, line)){
    std::istringstream iss(line);
    
    std::string head;
    std::string l;
    std::string h;
    std::string nextState;
    
    iss >> head;
    addNonTerminal_(head);
    
    iss >> l >> h;
    
    if(iss >> nextState){
      addNonTerminal_(nextState);
    }
    
    addTransition_(head,l,h,nextState);
  }
}


void
Parser::build(Nfa& nfa){
  for(auto& stateInfo : stateInfos_){
    buildState(nfa, stateInfo);
  }  
}


void
Parser::buildState(Nfa& nfa,
		   const StateInfo& stateInfo)
{
  // create a new nfa state for this
  const int stateIndex = nfa.addState(stateInfo.name_);
  
  // prepair the carrier array
  std::map<std::string, std::set<int> > carriers;
  
  // add end cases
  carriers[""] = std::set<int>();
  carriers["~"] = std::set<int>();
  
  for(auto& transition : stateInfo.transitions_){
    // add low
    carriers[transition.l_] = std::set<int>();
    std::string incH = transition.h_;
    if(incH == ""){
      incH.push_back(0x00);
    } else {
      incH.back()++;
    }
    carriers[incH] = std::set<int>();
  }
  
  // now color the carriers
  for(auto& transition : stateInfo.transitions_){
    
    auto il = carriers.lower_bound(transition.l_);
    auto ih = carriers.upper_bound(transition.h_);
    
    for(auto i = il; i!=ih; ++i){
      i->second.insert(transition.nextState_);
    }
  }
  
  // now merge intervals of same color
  for(auto p =carriers.begin();
      p != carriers.end(); ++p){
    auto n = p;  n++;
    if(carriers.end() == n) break;
    
    if(p->second.size() == n->second.size()){
      if(std::equal(p->second.begin(), p->second.end(),
		    n->second.begin())) {
	carriers.erase(p);
	continue;
      }
    }
  }
  
  // now emit merged intervals
  for(auto il =carriers.begin();
      il != carriers.end(); ++il){
    auto ih = il; ih++;
    
    const int transitionIndex
      = nfa.addTransition(stateIndex,il->first);
    
    for(int nextState : il->second){
      nfa.addNextStateToTransition(stateIndex,
				   transitionIndex,
				   nextState);
    }
  }
}



