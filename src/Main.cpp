#include <iostream>
#include "State.hpp"
#include "Action.hpp"
#include "Problem.hpp"
#include "Node.hpp"

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>

using std::vector;
using std::set;
using std::find;
using std::cout;	using std::endl;
//helper function that generates all of the possible actions that can be performed.
vector<Action> get_all_actions();
//prototype for test
void test_check_valid();

int main(int argc, const char *argv[])
{
	vector<Action> all_actions = get_all_actions();

	for(vector<Action>::iterator it = all_actions.begin(); it != all_actions.end(); it++){
		cout << it->get_direction() << " ; " << it->get_person1() << " ; " << it->get_person2() << endl;
	}

	test_check_valid();
 	return 0;
}

/*
Create actions for all possible combination of Direction, Person1, Person2
The fact that enumerations are represented as integers is utilized to loop create all of the combinations

The Person and Direction enums, which are defined in Action.hpp are repeated here for clarity's sake

enum Person{MISSIONARY, CANNIBAL, NONE};
enum Direction{LEFT, RIGHT};


*/
vector<Action> get_all_actions(){
	//vector in which to store all unique actions.
	vector<Action> result_vector;
	//i represents the first passenger in the action
	for(int i = MISSIONARY; i != NONE; i++){
		//j represents the second passenger in the action. Because the second passenger can be NONE, the break condition will be j != NONE+1.
		for(int j = MISSIONARY; j != NONE + 1; j++){
			//k represents the direction of movement.  The break condition will be k != RIGHT+1 for the same reason as stated for the Person2 loop.
			for(int k = LEFT; k != RIGHT + 1; k++){
				//'Action action_generated(0, 0, 0)' is equivalent to 'Action action_generated(LEFT, MISSIONARY, MISSIONARY)'
				Action action_generated((Direction)k, (Person)i, (Person)j);

				//if the action is not already in the vector, add it
				if(find(result_vector.begin(), result_vector.end(), action_generated) == result_vector.end())
					result_vector.push_back(action_generated);
			}
		}
	}


	return result_vector;
}

//no unit testing framework currently, so just using a method to test the check valid action function
//Feel free to test if I missed any edge cases
//DELETE before submission
void test_check_valid()
{
	State test1_state;
	Action test1_action(LEFT, CANNIBAL, CANNIBAL); //wrong direction

	State test2_state;
	Action test2_action(RIGHT, CANNIBAL, CANNIBAL);
	Action test21_action(RIGHT, NONE, NONE); //no person on boat

	State test3_state({2, 1}, {2, 1}, false);
	Action test3_action(LEFT, CANNIBAL, MISSIONARY);
	Action test31_action(LEFT, MISSIONARY, CANNIBAL);
	Action test32_action(LEFT, MISSIONARY, NONE);
	Action test33_action(LEFT, CANNIBAL, NONE); //cannibals outnumber missionaries on left side
	Action test34_action(LEFT, CANNIBAL, CANNIBAL); //too many cannibals taken
	Action test35_action(RIGHT, CANNIBAL, MISSIONARY); //wrong direction

	State test4_state({2, 1}, {2, 1}, true);
	Action test4_action(RIGHT, MISSIONARY, MISSIONARY);
	Action test41_action(RIGHT, MISSIONARY, NONE); //cannibals outnumber missionaries on left side

	//flip numbers just for code coverage
	State test5_state({1, 2}, {1, 2}, false);
	Action test5_action(LEFT, MISSIONARY, MISSIONARY);
	Action test51_action(LEFT, MISSIONARY, NONE); //cannibals outnumber missionaries on right side

	cout << "TEST 1 VALUE: " << ((Action::check_valid_action(test1_state, test1_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //wrong direction
	cout << "TEST 2 VALUE: " << ((Action::check_valid_action(test2_state, test2_action)) ? "TRUE " : "FALSE ") << "EXPECTED: TRUE" << endl;
	cout << "TEST 21 VALUE: " << ((Action::check_valid_action(test2_state, test21_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //no person on boat
	cout << "TEST 3 VALUE: " << ((Action::check_valid_action(test3_state, test3_action)) ? "TRUE " : "FALSE ") << "EXPECTED: TRUE" << endl;
	cout << "TEST 31 VALUE: " << ((Action::check_valid_action(test3_state, test31_action)) ? "TRUE " : "FALSE ") << "EXPECTED: TRUE" << endl;
	cout << "TEST 32 VALUE: " << ((Action::check_valid_action(test3_state, test32_action)) ? "TRUE " : "FALSE ") << "EXPECTED: TRUE" << endl;
	cout << "TEST 33 VALUE: " << ((Action::check_valid_action(test3_state, test33_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //cannibals outnumber missionaries on left side
	cout << "TEST 34 VALUE: " << ((Action::check_valid_action(test3_state, test34_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //too many cannibals taken
	cout << "TEST 35 VALUE: " << ((Action::check_valid_action(test3_state, test35_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //wrong direction
	cout << "TEST 4 VALUE: " << ((Action::check_valid_action(test4_state, test4_action)) ? "TRUE " : "FALSE ") << "EXPECTED: TRUE" << endl;
	cout << "TEST 41 VALUE: " << ((Action::check_valid_action(test4_state, test41_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //cannibals outnumber missionaries on left side
	cout << "TEST 5 VALUE: " << ((Action::check_valid_action(test5_state, test5_action)) ? "TRUE " : "FALSE ") << "EXPECTED: TRUE" << endl;
	cout << "TEST 51 VALUE: " << ((Action::check_valid_action(test5_state, test51_action)) ? "TRUE " : "FALSE ") << "EXPECTED: FALSE" << endl; //cannibals outnumber missionaries on right side

}