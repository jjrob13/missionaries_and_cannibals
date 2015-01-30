#ifndef GUARD_State_hpp
#define GUARD_State_hpp

#include <array>
class State{
private:
	std::array<int, 2> missionaries;
	std::array<int, 2> cannibals;
	bool boat_is_on_left;
public:
	State(std::array<int, 2>, std::array<int, 2>, bool);
	State();

	std::array<int, 2> get_missionary_array();
	std::array<int, 2> get_cannibal_array();
	//overloading the '==' operator for easy state comparison.
	bool operator==(const State & s){
		return (this->missionaries[0] == s.missionaries[0]) && (this->missionaries[1] == s.missionaries[1]) &&
				(this->cannibals[0] == s.cannibals[0]) && (this->cannibals[1] == s.cannibals[1]);
	}
};

#endif