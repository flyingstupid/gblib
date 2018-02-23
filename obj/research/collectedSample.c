//
//  /obj/research/collectedSample.c
//  GB Mud
//


inherit OBJECT;


int get_examine_value();
void set_examine_value(int value);

int get_research_time();
void set_research_time(int value);

string get_type();
void set_type(string type);


/*  Global variables */
int ExamineValue;
int ResearchTime;
string SampleType;



int get_examine_value(){
    return ExamineValue;
}
void set_examine_value(int value){
    ExamineValue = value;
}


int get_research_time(){
    return ResearchTime;
}
void set_research_time(int value){
    ResearchTime = value;
}

string get_type(){
    return SampleType;
}
void set_type(string type){
    SampleType = type;
}



