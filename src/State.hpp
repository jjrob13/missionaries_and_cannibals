#ifndef GUARD_State_hpp
#define GUARD_State_hpp

#include <array>
class State{
private:

	//arrays represent how many of a given person-type are on the left or right side of the river
	//eg. if missionaries = {2, 1}	then there are two missionaries on the left side and one on the right side of the river.
	std::array<int, 2> missionaries;
	std::array<int, 2> cannibals;

	//boolean flag to identify the side of the river that the boat is on.
	bool boat_is_on_left;

public:
	//constructor params: (missionary_array, cannibal_array, boat_is_on_left_side)
	State(std::array<int, 2>, std::array<int, 2>, bool);
	State();

	//accessors
	std::array<int, 2> get_missionary_array();
	std::array<int, 2> get_cannibal_array();
	bool is_boat_on_left();
	
	//overloading the '==' operator for easy state comparison.
	bool operator==(const State & s){
		return (this->missionaries[0] == s.missionaries[0]) && (this->missionaries[1] == s.missionaries[1]) &&
				(this->cannibals[0] == s.cannibals[0]) && (this->cannibals[1] == s.cannibals[1]) && (this->boat_is_on_left == s.boat_is_on_left);
	}
};

#endif