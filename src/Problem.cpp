#include "Problem.hpp"
#include <algorithm>
#include <iterator>
using std::vector;

Problem::Problem(const State initial_state, const State goal_state, const std::vector<Action> & all_available_actions){
	this->initial_state = initial_state;
	this->goal_state = goal_state;
	this->all_available_actions = all_available_actions;
}

Problem::Problem(){

}


vector<Action> Problem::get_available_actions_from(const State & current_state){
	vector<Action> result;
	for (vector<Action>::iterator i = this->all_available_actions.begin(); i != all_available_actions.end(); ++i)
	{
		if(i->is_valid_action_from(current_state))
			result.push_back(*i);
	}

	return result;
}

bool Problem::goal_test(const State & current_state){
	return this->goal_state == current_state;
}