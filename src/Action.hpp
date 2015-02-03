#ifndef GUARD_Action_hpp
#define GUARD_Action_hpp
#include "State.hpp"
#include <string>
using std::string;


//enums to represent each actor and direction
enum Person{MISSIONARY, CANNIBAL, NONE};
enum Direction{LEFT, RIGHT};

class Action{

private:
	//instance variablea.
	Person person1, person2;
	Direction dir;

	const string person_to_string(Person);

public:

	//checks whether a state/action combo is valid.
	static bool check_valid_action(State &, Action &);

	//perform the action represented by the 'this' object on the passed state and return the resulting state.
	//A: S -> S
	State perform_action(State &);

	//Takes a direction and two people. eg. Action(LEFT, MISSIONARY, NONE) will create an action that moves one missionary from right to left.
	Action(Direction, Person, Person);
	Action();

	//Accessors
	Person get_person1();
	Person get_person2();
	Direction get_direction();

	//overloading the '==' operator for easy action comparison.
	bool operator==(const Action & a){
		//Direction of movement does not match
		if(this->dir != a.dir)
			return false;

		//Case 1: Passengers are identical. ie. (MISSIONARY, CANNIBAL) == (MISSIONARY, CANNIBAL);
		if(a.person1 == this->person1 && a.person2 == this->person2)
			return true;

		//Case 2: Same passengers, but different order. ie. (MISSIONARY, CANNIBAL) == (CANNIBAL, MISSIONARY);
		if(a.person1 == this->person2 && a.person2 == this->person1 && a.dir == this->dir)
			return true;

		//Case 3: different passengers.
		return false;
	}

	const string to_string();

};

#endif