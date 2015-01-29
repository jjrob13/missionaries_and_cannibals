#include "Node.hpp"

Node::Node(const State & state, Node *parent, const Action & action_from_parent, double total_path_cost_to_state){
	this->state = state;
	this->parent = parent;
	this->action_from_parent = action_from_parent;
	this->total_path_cost_to_state = total_path_cost_to_state;
}

Node::Node(){
	this->parent = 0;
}

const State Node::get_state(){
	return this->state;
}

Node* Node::get_parent_node(){
	return this->parent;
}

const Action Node::get_action(){
	return this->action_from_parent;
}

double Node::get_path_cost(){
	return total_path_cost_to_state;
}