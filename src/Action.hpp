#ifndef GUARD_Action_hpp
#define GUARD_Action_hpp
#include "State.hpp"


enum Person{MISSIONARY, CANNIBAL, NONE};
enum Direction{LEFT, RIGHT};

class Action{
public:
	static bool check_valid_action(State &, Action &);
	State perform_action(State &);
	Action(Direction, Person, Person);
	Action();

private:
	Person person1, person2;
	Direction dir;
};

#endif