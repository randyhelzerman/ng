#include <Parser.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
using namespace ng;


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
  stateInfos_[headIndex].transitions_.push_back(StateInfo::Transition(l,h,nextIndex));
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
