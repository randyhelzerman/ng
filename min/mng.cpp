#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>


class Mng {
public:
  
  struct IntervalTree_ {
    struct Entry_ {
      Entry_(const char letter, const int nextState) :
	letter_(letter),
	nextState_(nextState) {}
      
      bool operator < (const Entry_& entry) const {
	return letter_ < entry.letter_;
      }
      
      char letter_;
      int nextState_;
    };
    
    std::vector<Entry_> tree_;
    
    void startAddBatch(){
      tree_.clear();
    }
    
    void batchAdd(const char letter, const int nextState){
      tree_.push_back(Entry_(letter, nextState));
    }
    
    void endAddBatch(){
      // add the sentinals
      tree_.push_back(Entry_(0, -1));
      tree_.push_back(Entry_(0xFF, -1));
      
      // sort the vector
      std::sort(tree_.begin(), tree_.end());
    }
    
    template<typename S>
    S& operator<<(S& s) {
      for(auto& entry : tree_){
	s << entry;
      }
      s << std::endl;
    }
  };
  
  template<typename S>
  void parse(S& s){
    std::string line;
    while(std::getline(std::cin, line)){
      // skip lines which are too short
      if(line.length() < 5) continue;
      
      // skip lines whose first 4 chars are not spaces
      if(line.substr(0,4) != "    ") continue;
      
      // this is a string we want. Split it into
      // tokens.
      std::stringstream lineStream(line);
      std::string bluff;
      std::vector<std::string> tokens;
      while( lineStream >> bluff) {
	tokens.push_back(bluff);
      }
      
      for(auto& token : tokens){
	std::cout << token << std::endl;
      }
      std::cout << std::endl;
    }
  }
};


template<typename S>
S& operator<<(S& s, Mng::IntervalTree_::Entry_ entry){
  s << "[" << entry.letter_ << "->" << entry.nextState_ << ")";
  return s;
}
      



void test_Mng_IntervalTree_Entry_(){
  // Test constructor
  Mng::IntervalTree_::Entry_ entry('a',5);
  assert(entry.letter_ == 'a');
  assert(entry.nextState_ == 5);
  
  // test output operator
  std::stringstream ss;
  ss << entry;
  assert(std::string("[a->5)") == ss.str());
}




int main(){
  
}
