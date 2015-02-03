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
#include <deque>

#define STEP_COST 1 //all step costs for this problem is 1

using std::vector;
using std::set;
using std::find;
using std::cout;	using std::endl;
using std::deque;
//helper function that generates all of the possible actions that can be performed.
vector<Action> get_all_actions();

//prototype for test
void test_check_valid();

//function to generate a child node (not sure where to put this really)
Node * CHILD_NODE(Problem &, Node *, Action &);

//function to print out the list of actions from the goal state
void PRINT_SOLUTION(Node *);

bool BREADTH_FIRST_SEARCH(Problem &);
bool is_in_explored(deque<State> explored, State child_state);
bool is_in_frontier(deque<Node *> frontier, State child_state);

int main(int argc, const char *argv[])
{
	vector<Action> all_actions = get_all_actions();

	for(vector<Action>::iterator it = all_actions.begin(); it != all_actions.end(); it++){
		cout << it->get_direction() << " ; " << it->get_person1() << " ; " << it->get_person2() << endl;
	}

	//test_check_valid();
	
	//problem set-up
	State initial_state({3, 0}, {3, 0}, true);
	Action action(RIGHT, CANNIBAL, NONE);
	State goal_state({0, 3},{0, 3}, false);
	Problem main_problem(initial_state, goal_state, all_actions);

	//I WAS JUST TESTING THE is_in_frontier and is_in_explored functions

	State initial_state1({3, 0}, {3, 0}, true);
	deque<Node*> explored;
	Action empty;
	explored.push_back(new Node(main_problem.get_initial_state(), 0, empty, 0));

	cout << ((is_in_frontier(explored, goal_state)) ? "TRUE" : "FALSE") << endl;
	cout << ((is_in_frontier(explored, initial_state)) ? "TRUE" : "FALSE") << endl;

	BREADTH_FIRST_SEARCH(main_problem);

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
/*********** NOTE: 
if recieving the error "stack smashing detected", add "-fno-stack-protector" to the CMakeLists.txt flags

********************************************/
bool BREADTH_FIRST_SEARCH(Problem & problem)
{
	Action empty_action; //no initial action
	Node * init_node = new Node(problem.get_initial_state(), 0, empty_action, 0); //initial node created
	if(problem.goal_test(init_node->get_state())){ PRINT_SOLUTION(init_node); return true;} //if initial state passes, goal has been found

	deque<Node *>frontier; //frontier FIFO queue
	deque<State>explored; //explored SET 
	frontier.push_back(init_node); //add initial node to FIFO queue
	int loopcount =  0;
	while(true)
	{
		if(frontier.empty()){ return false;} //if the frontier is empty and no solution has been found, return false

		Node * node = frontier.front(); frontier.pop_front(); //pop a node in the front of the frontier
		State node_state = node->get_state(); //grab the state of the popped node
		explored.push_front(node_state); //add the state to the set
		
		vector<Action> problem_actions = problem.get_available_actions_from(node_state); //grab all the possible actions given a state
		for(vector<Action>::iterator it = problem_actions.begin(); it != problem_actions.end(); it++) //iterate through all of these possible actions
		{
			Node *child = CHILD_NODE(problem, node, *it); //generate a child node given the action iterated with
			State child_state = child->get_state(); //grab the state of the child node
			if(! ((is_in_explored(explored, child_state)) || (is_in_frontier(frontier, child_state)) ) ) //if the child_state is not in explored or frontier
			{
				if(problem.goal_test(child_state)){ PRINT_SOLUTION(child); return true;} //test for the solution
					
				frontier.push_back(child);
			}
		}
		cout << "LOOP: " << loopcount << endl; //just as a test to see that the program is still running
		++loopcount;
		 
	}

	return true;
}

//check if state is in the explored set
bool is_in_explored(deque<State> explored, State child_state)
{
	for(deque<State>::iterator it = explored.begin(); it != explored.end(); it++)
	{
		if(child_state == *it) {return true;}
	}

	return false;
}

//check if state is in the nodes of the frontier queue
bool is_in_frontier(deque<Node *> frontier, State child_state)
{
	for(deque<Node *>::iterator it = frontier.begin(); it != frontier.end(); it++)
	{
		if(child_state == (*it)->get_state()) {return true;}
	}

	return false;
}

//generates a new child node given a node, an action
Node * CHILD_NODE(Problem & current_problem, Node * parent_node, Action & applied_action){
	State current_state = parent_node->get_state();
	State new_state = applied_action.perform_action(current_state);
	int path_cost = parent_node->get_path_cost() + STEP_COST;
	return new Node(new_state, parent_node, applied_action, path_cost);
}

//prints the solution actions (backwards for now, change later)
void PRINT_SOLUTION(Node * final_node)
{
	cout << "SOLUTION TO BE PRINTED";
	string c;
	std::cin >> c; //temporary pause
	Node * temp_node = final_node;
	while(temp_node != 0){
		Action action_performed = temp_node->get_action();
		cout << "Action: " + action_performed.to_string() << endl;
		temp_node = temp_node->get_parent_node();
	}

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