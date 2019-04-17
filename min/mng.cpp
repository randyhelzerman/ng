#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>


namespace ng {

  // Represents a transition between states.
  struct Transition {
    unsigned char letter;
    int nextStateIndex;

    Transition(const char letter,
	       const int nextStateIndex=-1) :
      letter(letter),
      nextStateIndex(nextStateIndex) {}

    bool operator < (const Transition& entry) const {
      return letter < entry.letter;
    }
  };

  template<typename S>
  S& operator<<(S& s, const Transition& transition){
    // see if this is a sentinal to be printed especially
    if(0x00 == transition.letter){
      s << "[" << "start_sentinal" << "->" << transition.nextStateIndex << ")";
      return s;
    }

    if(0xFF == transition.letter){
      s << "[" << "end_sentinal" << "->" << transition.nextStateIndex << ")";
      return s;
    }

    s << "[" << transition.letter << "->" << transition.nextStateIndex << ")";
    return s;
  }

  void test_Transition(){
    // Test constructor
    Transition transition('a',5);
    assert(transition.letter == 'a');
    assert(transition.nextStateIndex == 5);

    // test output operator
    std::stringstream ss;
    ss << transition;
    assert(std::string("[a->5)") == ss.str());

    // Test operator <
    Transition transitionA('a',5);
    Transition transitionB('b',5);

    Transition transitionStartStransition(0x00,5);
    Transition transitionEndStransition(0xFF,5);

    assert(!(transition < transitionA));
    assert(transitionA  < transitionB);

    assert(transitionStartStransition <  transition);
    assert(transitionStartStransition < transitionA);
    assert(transitionStartStransition < transitionB);
    assert(transitionStartStransition < transitionEndStransition);

    assert(transition  < transitionEndStransition);
    assert(transitionA < transitionEndStransition);
    assert(transitionB < transitionEndStransition);
  }


  // Represents a state in the NDFA.
  struct State : public std::vector<Transition> {

    void addBatch(const char letter, const int nextStateIndex){
      push_back(Transition(letter, nextStateIndex));
    }

    void endAddBatch(){
      // add the sentinals
      push_back(Transition(0, -1));
      push_back(Transition(0xFF, -1));

      // sort the vector
      std::sort(begin(), end());
    }

    struct QueryRange : public std::pair<State::const_iterator,
					 State::const_iterator> {
      State::const_iterator begin() const {
	return first;
      }

      State::const_iterator end() const {
	return second;
      }
    };

    QueryRange queryRange(const unsigned char letter){
      QueryRange returner;

      // See if this letter is in the transitions
      returner.first = std::lower_bound(begin(), end(), Transition(letter));

      // if we didn't find the letter in any of the transitions, return the empty range.
      if(returner.first == end()
	 ||
	 returner.first->letter != letter) {
	returner.first = end();
	returner.second = end();
	return returner;
      }

      // Find the end of the transitions with this letter
      returner.second = std::upper_bound(begin(), end(), Transition(letter));
      return returner;
    }

  };


  template<typename S>
  S& operator<<(S& s, const State& state) {
    for(auto& transition : state){
      s << transition;
    }

    return s;
  }

  void test_State(){
    // Test batch creation
    State state;
    {
      state.addBatch('z',5);
      state.addBatch('n',1);
      state.addBatch('n',2);
      state.addBatch('n',3);
      state.addBatch('b',25);
      state.addBatch('a',100);
    } state.endAddBatch();

    // Test overloaded output operator
    std::stringstream ss;
    ss << state;
    std::string goldString("[start_sentinal->-1)[a->100)[b->25)[n->1)[n->2)[n->3)[z->5)[end_sentinal->-1)");
    assert(goldString
	   ==
	   ss.str());

    // Test case where we are querying a letter which occurs only once
    // in the interval state.
    {
      int count = 0;
      for(auto& transition : state.queryRange('b')){
	assert(transition.letter == 'b');
	count++;
      }
      assert(1==count);
    }

    // Test case where we are quering a letter which occurs
    // 3 times in the interval state
    {
      int count = 0;
      for(auto&  transition : state.queryRange('n')){
	assert(transition.letter == 'n');
	count++;
      }
      assert(3==count);
    }

    // Test case where we are querying a letter which does not
    // occur in the interval state
    {
      for(auto&  transition : state.queryRange('f')){
	assert(false);
      }
    }
  }



  struct SymbolTable {
    std::map<std::string, int> name2index;
    std::vector<std::string> index2name;
    std::vector<State> states;

    // gets or creates the index for the
    // state by this name.
    int addState(const std::string& name) {
      // If its already in the table, return the index
      auto i = name2index.find(name);
      if(name2index.end() != i) return i->second;

      // if its not, create a new transition for it
      name2index[name] = states.size();
      index2name.push_back(name);
      states.push_back(State());
      return states.size()-1;
    }

    // Gets the integer associated with this state name,
    // or -1 on error.  Does not change the symbol table.
    int getStateIndex(const std::string& stateName) const {
      auto i = name2index.find(stateName);
      if(i==name2index.end()) return -1;
      return i->second;
    }

    // run through all the states and end add batch them.
    void endAddBatchAll(){
      for(auto& state : states){
	state.endAddBatch();
      }
    }

    // ctor
    SymbolTable(){
      // every symbol table has the end state
      // at index 0
      addState("END STATE");
    }
  };


  template<typename S>
  S& operator<<(S& s, const SymbolTable& table) {
    for(int i=0;i<table.states.size(); i++){
      s << i << " : " << table.index2name[i] << " : " << table.states[i] << std::endl;
    }
    return s;
  }

  struct Ng {
    SymbolTable symbolTable;
    std::vector<int> visitedStates;

    bool parse(const std::string& rule,
	       const std::string& input){
      // initialize parsing
      for(auto& visitedState : visitedStates){
	visitedState = -1;
      }

      // get the initial state for this parse
      const int initialStateIndex = symbolTable.getStateIndex(rule);
      // if this state isn't in the NFA, we can't parse
      if(-1 == initialStateIndex) return false;

      std::vector<int> currentStates;
      currentStates.push_back(initialStateIndex);
      std::vector<int> nextStates;

      // run through the input string
      for(int inputPosition=0; inputPosition<input.size(); inputPosition++){
	processInputPosition(currentStates, input, inputPosition, nextStates);
	if(nextStates.size() == 0) return false;

	// move to next states
	std::swap(currentStates, nextStates);
      }

      // see if we are at the end state....if so, success
      auto finder = std::find(currentStates.begin(),
			      currentStates.end(),
			      0);
      return finder != currentStates.end();
    }

    void processInputPosition(const std::vector<int>&currentStates,
			      const std::string& input,
			      const int inputPosition,
			      std::vector<int>& nextStates){
      // initialize next states
      nextStates.clear();

      for(auto currentState : currentStates){
	expandState(currentState, input[inputPosition], inputPosition, nextStates);
      }
    }

    void expandState(const int currentStateIndex,
		     const unsigned char letter,
		     const int inputPosition,
		     std::vector<int>& nextStates){
      for(auto& transition : symbolTable.states[currentStateIndex].queryRange(letter)){
	nextStates.push_back(transition.nextStateIndex);
      }
    }


    template<typename S>
    void compile(S& s){
      std::string line;
      while(std::getline(std::cin, line)){
	// skip lines which are too short
	if(line.length() < 5) continue;

	// skip lines whose first 4 chars are not spaces
	if(line.substr(0,4) != "    ") continue;

	// this is a string we want. Split it into
	// tokens.
	std::stringstream lineStream(line);

	// attempt to fetch the from state
	std::string fromStateName;
	if(!(lineStream >> fromStateName)) continue;

	// throw away the arrow
	std::string arrow;
	if(!(lineStream >> arrow)) continue;

	// attempt to fetch the letter
	unsigned char letter;
	if(!(lineStream >> letter)) continue;

	// attempt to fetch the next state.
	// defaults to "END STATE"
	std::string nextStateName("END STATE");
	lineStream >> nextStateName;

	// Now that we know we've got a valid line,
	// we can process it.
	const int fromStateIndex=symbolTable.addState(fromStateName);
	const int nextStateIndex=symbolTable.addState(nextStateName);
	symbolTable.states[fromStateIndex].addBatch(letter, nextStateIndex);
      }

      // After the input is parsed, initialize the trees
      symbolTable.endAddBatchAll();
    }
  };


  template<typename S>
  S& operator<<(S& s, const Ng& ng) {
    s << ng.symbolTable << std::endl;
    return s;
  }


} // namespace ng
int main(){
  ng::Ng ng;
  ng.compile(std::cin);
  std::cout << ng;
}
