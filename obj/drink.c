// 
//     /obj/drink.c 
//     For all your beverage needs.
//     GB Mud
//

inherit OBJECT;

//Prototypes
void set_fill(int arg);
int get_fill();
int is_drink();
void set_selfDrinkMsg(string msg);
string get_selfDrinkMsg();
void set_roomDrinkMsg(string msg);
string get_roomDrinkMsg();

//Variables
int fill;
string selfDrinkMsg;
string roomDrinkMsg;

void set_fill(int arg)
{
    fill=arg;
}

void set_selfDrinkMsg(string msg)
{
    selfDrinkMsg=msg;
}

string get_selfDrinkMsg()
{
    return selfDrinkMsg;
}

void set_roomDrinkMsg(string msg)
{
    roomDrinkMsg=msg;
}

string get_roomDrinkMsg()
{
    return roomDrinkMsg;
}

int get_fill()
{
    return fill;
}

int is_drink()
{
    return 1;
}
