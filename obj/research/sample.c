//
//
// /obj/research/sample.c
// base code for the production of research samples
//
//

inherit OBJECT;

/* FUNCTION PROTOTYPES */
int get_collect_diff();
void set_collect_diff(int value);

int get_base_value();
void set_base_value(int value);

string get_type();
void set_type(string type);

int get_examine_time();
void set_examine_time(int value);

string get_vessel();
void set_vessel(string vessel);


/* GLOBAL VARIABLES */
int collectDiff;
int baseValue;
string sampleType;
int examineTime;
string collectionVessel;



int get_collect_diff()
{
    return collectDiff;
}

void set_collect_diff(int value)
{
    collectDiff = value;
}

int get_base_value()
{
    return baseValue;
}

void set_base_value(int value)
{
    baseValue = value; 
}

string get_type()
{
    return sampleType;
}
void set_type(string type)
{
    sampleType = type;
}


int get_examine_time(){
    return examineTime;
}
void set_examine_time(int value)
{
    examineTime = value;
}

string get_vessel()
{
	return collectionVessel;
}

void set_vessel(string vessel)
{
	collectionVessel = vessel;
}



