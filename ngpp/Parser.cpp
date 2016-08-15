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
  
  // bump the count
  nonTerminalCount_++;
}


void
Parser::parse(const std::string filename)
{
  initParsing_();
  
  std::ifstream infile(filename);
  
  std::string line;
  while (std::getline(infile, line)){
    std::istringstream iss(line);
    
    std::string token;
    while(iss >> token){
      std::cout << "token:" << token << "  ";
    }
    std::cout << std::endl;
    
  }
}
