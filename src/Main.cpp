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

int main(int argc, const char *argv[])
{
	vector<Action> all_actions = get_all_actions();

	for(vector<Action>::iterator it = all_actions.begin(); it != all_actions.end(); it++){
		cout << it->get_direction() << " ; " << it->get_person1() << " ; " << it->get_person2() << endl;
	}
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