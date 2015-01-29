#ifndef GUARD_Problem_hpp
#define GUARD_Problem_hpp

#include "State.hpp"
#include "Action.hpp"
#include <vector>
class Problem
{

private:
	State initial_state, goal_state;
	std::vector<Action> all_available_actions;
public:
	Problem(const State, const State, const std::vector<Action> &);
	Problem();
	//get all available actions from a given state
	std::vector<Action> get_available_actions_from(const State &);

	bool goal_test(const State &);

};
#endif