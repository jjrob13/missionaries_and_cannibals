#include "State.hpp"
#include <sstream>
using std::stringstream;
using std::array;
using std::string;

State::State(array<int, 2> missionaries, array<int, 2> cannibals, bool boat_is_on_left){
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
array<int, 2> State::get_missionary_array(){
	array<int, 2> copy_of_array = this->missionaries;
	return copy_of_array;
}

//returns a copy of the cannibal array so that the orignal array is not modified in any way.
array<int, 2> State::get_cannibal_array(){
	array<int, 2> copy_of_array = this->cannibals;
	return copy_of_array;
}

//returns boolean variable on the current location of the boat
bool State::is_boat_on_left(){
	return this->boat_is_on_left;
}

/*
Take the initial state, where there are three missionaries, three cannibals, and the boat on the left, this 
function will print it out in the following form:

MMM
B
CCC

*/
const string State::to_string() const{
	stringstream result;
	string::size_type width_of_first_col = 6;
	
	//add left missionaries
	result << string((this->missionaries)[0], 'M');

	//add padding
	result << string(width_of_first_col - (this->missionaries)[0], ' ');

	//add right missionaries
	result << string((this->missionaries)[1], 'M');

	result << '\n';


	//add left cannibals
	result << string((this->cannibals)[0], 'C');

	//add padding
	result << string(width_of_first_col - (this->cannibals)[0], ' ');

	//add right cannibals
	result << string((this->cannibals)[1], 'C');


	result << '\n';

	//add boat
	if(boat_is_on_left)
		result << "B";
	else
		result << string(width_of_first_col, ' ') << "B";

	return result.str();

}