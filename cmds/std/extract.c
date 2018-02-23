//
//  /cmds/std/extract.c
//  GB mud
//



inherit COMMAND;
inherit OBJECT;


/* Function prototypes */
string which_antislime();
void make_antislime_green();
void make_antislime_orange();
void make_antislime_purple();
void make_antislime_gold();
int do_extract();


/* GLOBAL VARIABLES */
object sample;
int test;


int main (string arg){
    object equipment;
    
    equipment = present ("extractor", environment(this_player()));
    sample = present(arg, this_player());
    
    if (!equipment)
    {
        return(notify_fail("Your lab is not equiped for this sort of research.\n"));
    }
    if (!this_player()->get_skill("extract"))
    {
        return(notify_fail("You are not certified to use this equipment.\n"));
    }
    if (!sample)
    {
        return(notify_fail("You do not have that sample.\n"));
    }
    if ((sample->get_type()!= "slime")){
        return(notify_fail("This piece of equpiment only works on slime samples.\n"));
    }
    
    tell_object(this_player(), "You begin the complex process of extracting the slime.\n");

    
    call_out("do_extract", 10);
    
    return 1;
}

int do_extract()
{
    string slimeFunction;
    string antislimeType;
    
    test=this_player()->DoSkillRoll("extract");
    if (test>0)
    {
        antislimeType = which_antislime();
        
        slimeFunction = "make_antislime_" + antislimeType;
        call_out(slimeFunction, 2);
    }
    else
    {
        destruct(sample);
        tell_object(this_player(), "You spill the sample and can not extract anything from it.\n");
    }
    
    return 1;

}
    
    

//skill test to determine pass or fail 

//skill test to determine which anti-slime is extracted.

string which_antislime(){
    int chance;
    int roll;
    
    chance = (this_player()->get_skill("extract")/20);
    roll = random (100) + 1;
    
    if (roll >= (100 - chance))
    {
        return "gold";
    }
    if ((roll >= (100 - chance * 3)) && roll < (100 - chance))
    {
        return "purple";
    }
    if ((roll >= (100 - chance * 6)) && roll < (100 - chance* 3))
    {
        return "orange";
    }
    else
    {
        return "green";
    }
}

void make_antislime_green(){
    
    object newAntislime;
    
    tell_object(this_player(), "You successfully extract some green anti-slime.\n");
    newAntislime= clone_object("/obj/research/greenantislime.c");
    newAntislime-> set_potency(this_player()->get_skill("extract"));
    
    newAntislime->move(this_player());

}

void make_antislime_orange(){
    
    object newAntislime;
    
    tell_object(this_player(),  "You successfully extract some orange anti-slime.\n");
    newAntislime = clone_object("/obj/research/orangeantislime.c");
    newAntislime -> set_potency(this_player()->get_skill("extract"));
    
    newAntislime->move(this_player());
    
}

void make_antislime_purple(){
    
    object newAntislime;
    
    tell_object(this_player(),  "You successfully extract some purple anti-slime.\n");
    newAntislime= clone_object("/obj/research/purpleantislime.c");
    newAntislime-> set_potency(this_player()->get_skill("extract"));
    
    newAntislime->move(this_player());
    
}

void make_antislime_gold(){
    
    object newAntislime;
    
    tell_object(this_player(),  "You successfully extract some gold anti-slime.\n");
    newAntislime= clone_object("/obj/research/goldantislime.c");
    newAntislime-> set_potency(this_player()->get_skill("extract"));
    
    newAntislime->move(this_player());
    
}






