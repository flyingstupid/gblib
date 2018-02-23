//
//  /cmds/std/train.c
//  GB mud
//

inherit COMMAND;


/* FUNCTION PROTOTYPES */

//string GetTrainer( string arg );
void DoTraining(object trainer);
int HasTrainer(string trainerName);
int CanTrain();
int DoRoll(int skill, int diff);
void AdvanceSkil(string skill);
void Finish();
/* GLOBAL VARIABLES */
object trainer;

int main(string arg){
    int i, delay;
    
    //tell_object( this_player(), "The arg is " + arg + "\n");
    
    if ( !arg || arg == ""){
        tell_object( this_player(), "You need to specify a trainer to use. \n");
        return 1;
    }
     
    trainer = present(arg, environment(this_player()));
    
    if(!trainer){
        return(notify_fail("You can't find that here!\n"));
    }
    	
    //tell_object( this_player(), "You will train on the " + trainer->query_short() + "\n");
    //tell_object(this_player(), this_player()->getLastTrain() + "  " + this_player()->getNumTrain() + "\n" );
    
    if (HasTrainer(arg)){
        if (CanTrain()){
            tell_object( this_player() , trainer->getStart() + "\n");
            
            i = 0;
            while (i<5){
                delay = (5*i);
                call_out("DoTraining", delay, trainer);
                i++;
            }
            call_out("Finish", delay);
        }
    }
    return 1;
}

void Finish(){
    tell_object( this_player() , trainer->getFinish() + "\n");
}


void DoTraining(object trainer){
    int skillRole;
    string skill;
    int diff;
    int skillValue;
    
    
    skill = trainer->getTrainerSkill();
    skillValue = this_player()->get_skill(skill);

    
   // skill = trainer() -> GetTrainerSkill();
    diff = trainer -> getDifficulty();
    
    //tell_room( environment( this_player() ), "the difficulty is " + diff + "\n");
    //tell_object( this_player() , "the difficulty is " + diff + "\n");
    skillRole = DoRoll(skillValue ,diff);
    //tell_room( environment( this_player() ), "the skill rolls is " + skillRole + "\n");
    tell_object( this_player() , "the skill rolls is " + skillRole + "\n");
    
    if (skillRole > 20){
        write (trainer->getCritSuccess() + "\n");
        this_player()->DoSkillXp(trainer->getTrainerSkill(), diff);
        this_player()->DoSkillXp(trainer->getTrainerSkill(), diff);
        return;
    }
    if (skillRole > 1){
        write (trainer->getSuccess() + "\n");
        return;
     }
    if (skillRole < -20){
        this_player()->CauseDamage(5);
        write (trainer->getCritFail() + "\n");
        return;
    }
     else{
        write (trainer->getFail() + "\n");
     }
}



int HasTrainer(string trainerName){
    object *room;
    object trainer;
    
    trainer = present( trainerName, environment( this_player()));
    
    if( trainer && is_a ("/obj/train/trainer.c", trainer )){
           // tell_object( this_player() , "You have found the  " + trainer + "\n");
            return 1;

    }
    tell_object( this_player() , "You can't seem to find the " + trainer + "\n");
    return 0;

}

int CanTrain(){
    if ((time() - this_player()->getTrainTime2()) > 86400 ){
        this_player()->setTrainTime2(this_player()->getTrainTime1());
        this_player()->setTrainTime1(time());
        return 1;
    }
    tell_object( this_player(), "You have already trained enough today, go out and put those skills to use!\n");
        return 0;
}

        
 
int DoRoll(int skill, int diff){
    int d100;
    int skillValue;
    int returnValue;
    
    if( undefinedp( diff ) ){
        diff=0;
    }
    
    d100=random(100)+1;
    skillValue = skill - diff;
    
    returnValue = skillValue-d100;
    
    //tell_object(this_player(), "Rolling: [" + trainer->getTrainerSkill() + "] of "+ skillValue +" @ Difficulty of [" + diff +"]  Roll was: ["+ d100 + "]\n" + "Result:" + returnValue + ".\n");
    
    if (d100 < skillValue){
        this_player()->DoSkillXp(trainer->getTrainerSkill(), diff);
    }
    return returnValue;
}
