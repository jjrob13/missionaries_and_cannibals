#ifndef GUARD_Node_hpp
#define GUARD_Node_hpp
#include "Action.hpp"
#include "Node.hpp"
#include "State.hpp"


//keeps track of the parent node via a Node pointer.
//To save memory, the State and Action members are passed via reference.
class Node{
private:
	State state;
	Node * parent;
	Action action_from_parent;
	double total_path_cost_to_state;

public:
	Node(const State &, Node *, const Action &, double);
	Node();
	const State get_state();
	Node* get_parent_node();
	const Action get_action();
	double get_path_cost();
};
#endif