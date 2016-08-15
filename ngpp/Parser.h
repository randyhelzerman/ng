#ifndef NGPP_PARSER__H
#define NGPP_PARSER__H

#include <string>
#include <unordered_map>


namespace ng {
  
  class Parser {
    int nonTerminalCount_;
    std::unordered_map<std::string,int> nonTerminals_;
    
    void initParsing_();
    void addNonTerminal_(const std::string& name);
    
  public:
    void parse(const std::string filename);
  };
  
  
};
    

#endif

