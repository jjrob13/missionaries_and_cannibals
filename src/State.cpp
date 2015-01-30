#include "State.hpp"

using std::array;

State(array<int, 2> missionaries, array<int, 2> cannibals, bool boat_is_on_left){
	this->missionaries = missionaries;
	this->cannibals = cannibals;
	this->boat_is_on_left = boat_is_on_left;
}

//the default constructor creates the initial state.
State::State(){
	this->missionaries = {3, 0};
	this->cannibals = {3, 0};
	this->boat_is_on_left = true;
}


//returns a copy of the missionary array so that the orignal array is not modified in any way.
array State::get_missionary_array(){
	array<int, 2> copy_of_array = this->missionaries;
	return copy_of_array;
}

//returns a copy of the cannibal array so that the orignal array is not modified in any way.
array State::get_cannibal_array(){
	array<int, 2> copy_of_array = this->cannibals;
	return copy_of_array;
}
