#include "Action.hpp"
#include <stdexcept>

Action::Action(){
	perform_action_member_function = NULL;
	check_valid_action_member_function = NULL;
}

Action::Action(State perform_action_member_function(const State &), bool check_valid_action_member_function(const State &)){
	perform_action_member_function = perform_action_member_function;
	check_valid_action_member_function = check_valid_action_member_function;
}

State Action::perform_action(const State & current_state){
	if(perform_action_member_function == NULL)
		throw std::logic_error("No action function defined");
	return (*perform_action_member_function)(current_state);
}


bool Action::is_valid_action_from(const State & current_state){
	if(check_valid_action_member_function == NULL)
		throw std::logic_error("No check valid action function defined");
	
	return (*check_valid_action_member_function)(current_state);
}