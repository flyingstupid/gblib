//
//  /obj/research/equipment.c
//  GB Mud
//

inherit OBJECT;

//FUNCTION PROTOTYPES

void set_cost(int value);
int get_cost();
int prevent_get();
void set_location(string loc);
string get_location();

//variables
int cost;
string location;


void set_cost(int value){
    cost = value;
}
int get_cost(){
    return cost;
}

int prevent_get(){
    return 1;
}

void set_location(string loc){
    location = loc;
}

string get_location(){
    return location;
}
