#ifndef GUARD_State_hpp
#define GUARD_State_hpp

class State{
public:
	int num_left_missionaries;
	int num_right_missionaries;
	int num_left_cannibals;
	int num_right_cannibals;
	State(int num_left_cannibals, int num_left_missionaries, int num_right_cannibals, int num_right_missionaries);
	State();


	//overloading the '==' operator for easy state comparison.
	bool operator==(const State & s){
		return (this->num_right_missionaries == s.num_right_missionaries) && (this->num_left_missionaries == s.num_left_missionaries) &&
				(this->num_left_cannibals == s.num_left_cannibals) && (this->num_right_cannibals == s.num_right_cannibals);
	}
};

#endif