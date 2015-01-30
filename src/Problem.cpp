#include "Problem.hpp"
#include <algorithm>
#include <iterator>
using std::vector;

Problem::Problem(const State initial_state, const State goal_state, const std::vector<Action> & all_available_actions){
	this->initial_state = initial_state;
	this->goal_state = goal_state;
	this->all_available_actions = all_available_actions;
}



//returns a vector of all actions that can be performed from a given state.
vector<Action> Problem::get_available_actions_from(State current_state){

	vector<Action> result;

	//loop through all actions
	for (vector<Action>::iterator i = this->all_available_actions.begin(); i != all_available_actions.end(); ++i)
	{
		//if the action can be performed, perform it.
		if(Action::check_valid_action(current_state, *i));
			result.push_back(*i); //add to result vector
	}

	return result;
}

bool Problem::goal_test(const State & current_state){
	return this->goal_state == current_state;
}