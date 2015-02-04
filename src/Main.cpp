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

//function to generate a child node (not sure where to put this really)
Node * CHILD_NODE(Problem &, Node *, Action &);

//function to print out the list of actions from the goal state
void PRINT_SOLUTION(Node *);

//Performs BFS on the Problem, and prints solution if one exists
bool BREADTH_FIRST_SEARCH(Problem &);

//macros/functions to implement depth limited search
#define FAILURE 0
#define CUTOFF 1
#define SOLUTION 2
int DEPTH_LIMITED_SEARCH(Problem &, int);
int RECURSIVE_DLS(Node *, Problem &, int);

//helper functions to see if a state is a member of either the explored or frontier sets
bool is_in_explored(deque<State> explored, State child_state);
bool is_in_frontier(deque<Node *> frontier, State child_state);

//main function
int main(int argc, const char *argv[]){
	vector<Action> all_actions = get_all_actions();	
	//problem set-up
	State initial_state({3, 0}, {3, 0}, true);
	Action action(RIGHT, CANNIBAL, NONE);
	State goal_state({0, 3},{0, 3}, false);
	Problem main_problem(initial_state, goal_state, all_actions);

	BREADTH_FIRST_SEARCH(main_problem);

	//DEPTH_LIMITED_SEARCH(main_problem, 12);
	cout << "Program end" << endl;
 	return 0;
}

//Function that implements Breadth-first search. Returns true if there is a solution, false if there is not
bool BREADTH_FIRST_SEARCH(Problem & problem){
	Action empty_action; //no initial action
	Node * init_node = new Node(problem.get_initial_state(), 0, empty_action, 0); //initial node created

	deque<Node *>frontier; //frontier FIFO queue
	deque<State>explored; //explored SET 
	frontier.push_back(init_node); //add initial node to FIFO queue
	
	while(true){ //while the solution has not been found or the solution search has failed
		if(frontier.empty()){ return false;} //if the frontier is empty and no solution has been found, return false

		Node * node = frontier.front(); frontier.pop_front(); //pop a node in the front of the frontier
		State node_state = node->get_state(); //grab the state of the popped node
		explored.push_front(node_state); //add the state to the set
		
		vector<Action> problem_actions = problem.get_available_actions_from(node_state); //grab all the possible actions given a state

		for(vector<Action>::iterator it = problem_actions.begin(); it != problem_actions.end(); it++){ //iterate through all of these possible actions
			Node *child = CHILD_NODE(problem, node, *it); //generate a child node given the action iterated with
			State child_state = child->get_state(); //grab the state of the child node
			if(! (is_in_explored(explored, child_state) || is_in_frontier(frontier, child_state) ) ){ //if the child_state is not in explored or frontier
				if(problem.goal_test(child_state)){ //test for the solution
					PRINT_SOLUTION(child);
					cout << "Total Path Cost of Solution: " << child->get_path_cost() << endl;
					return true;
				} 
				frontier.push_back(child);
			}
		}
	}
	return true;
}

//Functions to implement Depth-limited search, straight implementation of book pseudocode in russel/norvig
int DEPTH_LIMITED_SEARCH(Problem & problem, int limit){
	Action empty_action; //no initial action
	Node * init_node = new Node(problem.get_initial_state(), 0, empty_action, 0); //initial node created

	return RECURSIVE_DLS(init_node, problem, limit);
}
int RECURSIVE_DLS(Node * node, Problem & problem, int limit){
	if(problem.goal_test(node->get_state())){ //test for the solution
		PRINT_SOLUTION(node);
		cout << "Total Path Cost of Solution: " << node->get_path_cost() << endl;
		return SOLUTION;
	} else if(limit == 0){
		return CUTOFF;
	}
	else{
		bool cutoff_occured = false;
		vector<Action> problem_actions = problem.get_available_actions_from(node->get_state()); //grab all the possible actions given a state

		for(vector<Action>::iterator it = problem_actions.begin(); it != problem_actions.end(); it++){ //iterate through all of these possible actions
			Node *child = CHILD_NODE(problem, node, *it); //generate a child node given the action iterated with
			int result = RECURSIVE_DLS(child, problem, limit - 1);
			if(result == CUTOFF){
				cutoff_occured = true;
			} else if(result != FAILURE){
				return result;
			}
		}
		
		if(cutoff_occured){
			return CUTOFF;
		} else {
			return FAILURE;
		}
	}
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

//check if state is in the explored set
bool is_in_explored(deque<State> explored, State child_state){
	for(deque<State>::iterator it = explored.begin(); it != explored.end(); it++){
		if(child_state == *it) {return true;}
	}
	return false;
}

//check if state is in the nodes of the frontier queue
bool is_in_frontier(deque<Node *> frontier, State child_state){
	for(deque<Node *>::iterator it = frontier.begin(); it != frontier.end(); it++){
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

//solution now prints in the correct order using recursion
void PRINT_SOLUTION(Node * final_node){
	if(final_node->get_parent_node() == NULL){
		cout << "Start State: " << endl;
		cout << (final_node->get_state()).to_string() << endl << endl;
		return;
	}

	PRINT_SOLUTION(final_node->get_parent_node());
	Action action_performed = final_node->get_action();
	cout << "Action: " + action_performed.to_string() << endl;

	cout << (final_node->get_state()).to_string() << endl << endl;
}