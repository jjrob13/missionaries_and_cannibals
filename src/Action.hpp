#ifndef GUARD_Action_hpp
#define GUARD_Action_hpp
#include "State.hpp"

class Action{
private:
	State (*perform_action_member_function)(const State &);
	bool (*check_valid_action_member_function)(const State &);
public:
	/*
	The constructor takes two function pointers:

	first: a function takes a state and returns the resulting state after performing an action.
	second: a function that takes a state and checks to see if the action can be performed on that state.

	*/
	Action(State (const State &), bool (const State &));
	Action();
	State perform_action(const State &);

	bool is_valid_action_from(const State &);
};
#endif