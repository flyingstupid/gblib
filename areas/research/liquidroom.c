//
//  /areas/research/liquidroom.c
//  GB Mud
//

inherit COMMAND;
inherit ROOM;

/* Function prototypes */
string which_serum();
void make_serum_blue();
void make_serum_cloudy();
void make_serum_pink();
void make_serum_silver();
int do_purify();
void half_message();
string *equipmentArray = ({});
void add_equip(string newEquip);
int get_equip(string getEquip);

/* GLOBAL VARIABLES */
object sample;
int Test;


void create()
{
    ::create();
    
    set_light(1);
    set_short("Liquid Laboratory");
    set_long(
             "This room is made entirely of granite and stainless steel.  \n"
             "There is a large drain in the center of the floor and nearly\n"
             "every inch of the room looks like it could merely be hosed\n"
             "down if the need arose.\n"
             );
}

void init()
{
    add_action("purify", "purify");
    add_action("aggregate", "aggregate");
}

void add_equip(string newEquip)
{
    equipmentArray += ({ newEquip });
}

int get_equip(string getEquip)
{
    int foundIndex;
    
    foundIndex = member_array( getEquip, equipmentArray );
    if (foundIndex == -1){
        return 0;
    }
    return 1;
}

/*-----------------------------------------------------------------------
 ------------------------  PURIFY FUNCTIONS  ----------------------------
 ------------------------------------------------------------------------*/



int main (string arg){
    object sample;
    
    
    sample = present(arg, this_player());
    
    if (!get_equip("extractor"))
    {
        return(notify_fail("Your lab is not equiped to purify liquids.\n"));
    }
    
    if (!this_player()->get_skill("purify"))
    {
        return(notify_fail("You are not certified to use this equipment.\n"));
    }
    if (!sample)
    {
        return(notify_fail("You do not have that sample.\n"));
    }
    if ((sample->get_type()!= "liquid")){
        return(notify_fail("This piece of equpiment only works on liquid samples.\n"));
    }
    
    tell_object(this_player(), "You begin the complex process of purifying the liquid.\n");
    
    call_out("half_message", 10);
    
    call_out("do_purify", 20);
    
    return 1;
}

void half_message()
{
    tell_object(this_player(), "The liquid swirls throught he glass tubes and begins dripping from the end of the purifier.\n");
}

int do_purify()
{
    string serumFunction;
    string serumType;
    
    Test=this_player()->DoSkillRoll("purify", 10);
    if (Test>1)
    {
        serumType = which_serum();
        
        serumFunction = "make_serum_" + serumType;
        call_out(serumFunction, 2);
    }
    else
    {
        destruct(sample);
        return(notify_fail("You spill the sample and can not purify anything from it.\n\n"));
    }
    return 1;
    
}



//skill test to determine pass or fail 

//skill test to determine which anti-slime is extracted.

string which_serum(){
    int chance;
    int roll;
    
    chance = (this_player()->get_skill("purify")/20);
    roll = random (100) + 1;
    
    if (roll >= (100 - chance))
    {
        return "silver";
    }
    if ((roll >= (100 - chance * 3)) && roll < (100 - chance))
    {
        return "pink";
    }
    if ((roll >= (100 - chance * 6)) && roll < (100 - chance* 3))
    {
        return "cloudy";
    }
    else
    {
        return "blue";
    }
}

void make_serum_blue(){
    
    object newSerum;
    
    tell_object(this_player(), "You successfully purify blue serum.\n");
    newSerum= clone_object("/obj/research/blueserum.c");
    newSerum-> set_potency(this_player()->get_skill("purify"));
    
    newSerum->move(this_player());
    
}

void make_antiserum_cloudy(){
    
    object newSerum;
    
    tell_object(this_player(), "You successfully purify a cloudy serum.\n");
    newSerum= clone_object("/obj/research/blueserum.c");
    newSerum-> set_potency(this_player()->get_skill("purify"));
    
    newSerum->move(this_player());
    
}

void make_serum_pink(){
    
    object newSerum;
    
    tell_object(this_player(), "You successfully purify a pink serum.\n");
    newSerum= clone_object("/obj/research/blueserum.c");
    newSerum-> set_potency(this_player()->get_skill("purify"));
    
    newSerum->move(this_player());
    
}

void make_serum_silver(){
    
    object newSerum;
    
    tell_object(this_player(), "You successfully purify a silver serum.\n");
    newSerum= clone_object("/obj/research/blueserum.c");
    newSerum-> set_potency(this_player()->get_skill("purify"));
    
    newSerum->move(this_player());
    
}
