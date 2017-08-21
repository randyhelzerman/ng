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


// just clear out nonterminals and terminals
// from last time parsing, and insert the stop
// state
void Parser::initParsing_()
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


// takes the data for a transition from the
// parser, and creates a transition to
// store it.   These transitions will
// be merged later to form the actual
// NFA
void
Parser::addTransition_(const std::string& head,
		       const std::string& l,
		       const std::string& h,
		       const std::string& nextState)
{
  // find the two states this transition bridges
  const int headIndex = nonTerminals_[head];
  const int nextIndex = nonTerminals_[nextState];
  
  // create the transition and store it
  stateInfos_[headIndex]
    .transitions_
    .push_back(StateInfo::Transition(l,h,nextIndex));
}


void
Parser::parse(const std::string filename)
{
  // clear out terminals and nonterminals
  // and ensure there is a stop state
  initParsing_();
  
  // Loop through the file line-by-lie
  std::ifstream infile(filename);
  std::string line;
  while (std::getline(infile, line)){
    // turn the line into a string stream
    // for easy parsage
    std::istringstream iss(line);
    
    // parse the head non-terminal
    std::string head;
    iss >> head;
    addNonTerminal_(head);
    
    // grab the low and high ranges
    std::string l,h;
    iss >> l >> h;

    // grab the next state...if its there
    std::string nextState;
    if(iss >> nextState){
      addNonTerminal_(nextState);
    }

    // now that we've parsed out all of the
    // data, add a transition which corresponds
    // with this line
    addTransition_(head,l,h,nextState);
  }
}


// now that we have all the states and transitions,
// we merge them niceliy.
void
Parser::build(Nfa& nfa){
  for(auto& stateInfo : stateInfos_){
    buildState(nfa, stateInfo);
  }  
}


// Takes all of the transitions going out of a state
// and converts them to one flat interval "tree"
void
Parser::buildState(Nfa& nfa,
		   const StateInfo& stateInfo)
{
  // prepair the carrier array
  std::map<std::string, std::set<int> > carriers;
  for(auto& transition : stateInfo.transitions_){
    // add low
    carriers[transition.l_] = std::set<int>();
    std::string incH = transition.h_;
    
    // add high
    if(incH == ""){
      // I don't know how useful this is...
      // we arn't suppose to have empty
      // ranges as input.
      incH.push_back(0x00);
    }
    // should work for UTF-8
    incH.back()++;
    carriers[incH] = std::set<int>();
  }

  // this is a stupid way to do it.  what are
  // you thinking man?
  
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
    // go to the next carrier if it exists
    auto n = p;  n++;
    if(carriers.end() == n) break;
    
    if(p->second.size() == n->second.size()){
      if(std::equal(p->second.begin(), p->second.end(),
		    n->second.begin())) {
	carriers.erase(n);
      }
    }
  }
  
  // create a new nfa state for this
  const int stateIndex = nfa.addState(stateInfo.name_);
  
  // now emit merged intervals
  for(auto il =carriers.begin();
      il != carriers.end(); ++il){
    auto ih = il; ih++;
    
    // don't add transitions which don't have next states
    if(il->second.empty()) continue;
    
    const int transitionIndex
      = nfa.addTransition(stateIndex,il->first,ih->first);
    
    for(int nextState : il->second){
      nfa.addNextStateToTransition(stateIndex,
				   transitionIndex,
				   nextState);
    }
  }
}



