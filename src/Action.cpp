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


bool Action::check_valid_action(State & current_state, Action & action_to_perform){
	
	//Needs to be implemented
	return true;
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