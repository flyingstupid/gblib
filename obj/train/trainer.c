//
//   /obj/train/trainer.c
//  GB mud
//


inherit OBJECT;



 /*Function prototypes*/
string getTrainerSkill();
void setTrainerSkill(string skill);
int getDifficulty();
void setDifficulty(int maxSkill);
void setStart(string startMsg);
string getStart();
void setFinish(string finishMsg);
string getFinish();
void setCritFailure(string CritFailMsg);
string getCritFail();
void setCritSuccess(string CritSucMsg);
string getCritSuccess();
void setFailure(string FailMsg);
string getFail();
void setSuccess(string SucMsg);
string getSuccess();


/*Global variables*/
string trainerSkill;
int difficulty;
string startMsg, finishMsg, CritSucMsg, CritFailMsg, FailMsg, SucMsg;

void create()
{
    set_id(({"Trainer", "trainer"}));
    set_short("a trainer");
    set_long ("a trainer sits here");
    setTrainerSkill("dodge");
    setDifficulty(0);
    setStart ("The trainer starts up");
    setFinish ("The trainer turns off");
    setCritFailure("You fail so miserably that you injure yourself");
    setCritSuccess("You perform so spectacularly that you gain extra training");
    setFailure("You fail!");
    setSuccess("You succeed!");
    
    
    
}

string getTrainerSkill(){
    return trainerSkill;
}

void setTrainerSkill(string skill){
    trainerSkill = skill;
}

int getDifficulty(){
    return difficulty;
}

void setDifficulty(int diff){
    difficulty = diff;
}


void setStart(string msg){
    startMsg = msg;
}

string getStart(){
    return startMsg;
}

void setFinish(string msg){
    finishMsg = msg;
}

string getFinish(){
    return finishMsg;
}

void setCritFailure(string msg){
    CritFailMsg = msg;
}

string getCritFail(){
    return CritFailMsg;
}

void setCritSuccess(string msg){
    CritSucMsg = msg;
}

string getCritSuccess(){
    return CritSucMsg;
}
void setFailure(string msg){
    FailMsg = msg;
}

string getFail(){
    return FailMsg;
}

void setSuccess(string msg){
    SucMsg = msg;
}

string getSuccess(){
    return SucMsg;
}

