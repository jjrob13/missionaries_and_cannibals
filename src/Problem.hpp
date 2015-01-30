#ifndef GUARD_Problem_hpp
#define GUARD_Problem_hpp

#include "State.hpp"
#include "Action.hpp"
#include <vector>

//class that resembles the "Problem" structure from the Russell/Norvig AI book
class Problem
{

private:
	State initial_state, goal_state;

	//all actions that are possible will be stored in this vector.
	std::vector<Action> all_available_actions;
public:

	//the constructor takes the initial state, final state, and a vector of actions
	Problem(const State, const State, const std::vector<Action> &);
	Problem();

	//get all available actions from a given state
	std::vector<Action> get_available_actions_from(State);

	//test whether the passed state is a goal state.
	bool goal_test(const State &);

};
#endif