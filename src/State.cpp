#include "State.hpp"

State::State(int num_left_cannibals, int num_left_missionaries, int num_right_cannibals, int num_right_missionaries){
	this->num_left_cannibals = num_left_cannibals;
	this->num_left_missionaries = num_left_missionaries;
	this->num_right_cannibals = num_right_cannibals;
	this->num_right_missionaries = num_right_missionaries;
}

State::State(){
	this->num_left_cannibals = 0;
	this->num_left_missionaries = 0;
	this->num_right_cannibals = 0;
	this->num_right_missionaries = 0;
}