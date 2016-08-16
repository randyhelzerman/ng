#include <Parser.h>

#include <iostream>

using namespace ng;

void
Parser::dump()
{
  // dump symbol table
  for(auto& i : nonTerminals_){
    std::cout << i.first << ":" << i.second << std::endl;
  }
  
  for(auto& stateInfo : stateInfos_){
    std::cout << "State:" << stateInfo.name_ << std::endl;
    for(auto& transition : stateInfo.transitions_){
      std::cout << "\t--> [" << transition.l_ << "-" << transition.h_ << "]\n";
    }
  }
  std::cout << std::endl;
}
