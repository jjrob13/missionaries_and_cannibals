#include "Action.hpp"
#include <array>
using std::array;
Action::Action(Direction dir, Person person1, Person person2){
	this->dir = dir;
	this->person1 = person1;
	this->person2 = person2;
}


/*
The 'Direction' enum is used to access the indices of the missionary and cannibal arrays.
The following code exploits the fact that due to the nature of enums:
	LEFT == 0;
	RIGHT == 1;

	
Example:
Let this be an action where dir = LEFT.

	//move one missionary from right to left
	missionaries[LEFT]++;
	missionaries[LEFT + 1]--;


Example where dir==RIGHT:
	//move one missionary from left to right
	missionary[RIGHT]++;
	missionary[(RIGHT + 1) % 2]--;

The key is that (RIGHT + 1) % 2 == 0 == LEFT

*/
State Action::perform_action(State & current_state){
	array<int, 2> missionaries = current_state.get_missionary_array();
	array<int, 2> cannibals = current_state.get_cannibal_array();

	if(this->person1 == MISSIONARY){

		missionaries[(int)this->dir]++;
		missionaries[((int)this->dir)+1 % 2]--;
	}else{
		cannibals[(int)this->dir]++;
		cannibals[((int)this->dir)+1 % 2]--;
	}

	//move person two if necessary
	if(this->person2 != NONE){
		if(this->person2 == MISSIONARY){
			missionaries[(int)this->dir]++;
			missionaries[((int)this->dir)+1 % 2]--;
		}else{
			cannibals[(int)this->dir]++;
			cannibals[((int)this->dir)+1 % 2]--;
		}
	}

	return State(missionaries, cannibals, this->dir == LEFT);
}

//static function to easily check against the set of rules if an action is valid given a state
bool Action::check_valid_action(State & current_state, Action & action_to_perform){
	if(current_state.is_boat_on_left()){ //if the current state has boat on the left, return false if boat is going left
		if(action_to_perform.get_direction() == 0){	return false; }
	}
	else{ //boat is currently on right, return false if boat is going right
		if(action_to_perform.get_direction() == 1){	return false; }
	}
	//check if the boat moves without any people
	if(action_to_perform.get_person1() == NONE && action_to_perform.get_person2() == NONE){ return false;}

	array<int, 2> missionaries = current_state.get_missionary_array();
	array<int, 2> cannibals = current_state.get_cannibal_array();

	int moving_miss = 0, moving_cann = 0, l_miss = missionaries[0], r_miss = missionaries[1], l_cann = cannibals[0], r_cann = cannibals[1];
	//count the number of missionaries and cannibals to move
	if(action_to_perform.get_person1() == 0){ 	moving_miss++; }
	else if(action_to_perform.get_person1() == 1){ 	moving_cann++; }

	if(action_to_perform.get_person2() == 0){ 	moving_miss++; }
	else if(action_to_perform.get_person2() == 1){ 	moving_cann++; }

	if(action_to_perform.get_direction() == 0) //boat going left->right
	{
		l_cann += moving_cann;
		l_miss += moving_miss;
		r_cann -= moving_cann;
		r_miss -= moving_miss;
	}
	else //boat going right->left
	{
		l_cann -= moving_cann;
		l_miss -= moving_miss;
		r_cann += moving_cann;
		r_miss += moving_miss;
	}

	if(l_cann < 0 || l_miss < 0 || r_cann < 0 || r_miss < 0){	return false; } //not enough number of miss/cann to move
	if((l_cann > l_miss) && l_miss != 0){	return false; } //after move, cannibals outnumber missionaries on left side
	if((r_cann > r_miss) && r_miss != 0){	return false; } //after move, cannibals outnumber missionaries on right side

	return true; //all checks have been passed
}

Person Action::get_person1(){
	return this->person1;
}

Person Action::get_person2(){
	return this->person2;
}

Direction Action::get_direction(){
	return this->dir;
}