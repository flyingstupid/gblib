//
//  /areas/research/slimeroom.c
//  GB Mud
//


inherit ROOM;


string *equipmentArray = ({});
void add_equip(string newEquip);
int get_equip(string getEquip);
string which_antislime();
void make_antislime_green();
void make_antislime_orange();
void make_antislime_purple();
void make_antislime_gold();
int do_extract();


/* GLOBAL VARIABLES */
object sample;
int test;

void create()
{
    ::create();
    
    set_light(1);
    set_short("Slime Annex");
    set_long(
             "This small annex is dominated by a large stainless steel fume.\n"
             "hood located along one wall.  There are several racks of vials and\n"
             "pipettes lined up on granite lab benches.  The rooms smells of antiseptic\n"
             "with just a hint of the pungent odor of ghost slime.\n"
             );
}

void init()
{
    add_action("extract", "extract");
    add_action("hybridize", "hybridize");
    add_action("infuse", "infuse");
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
 --------------------------  EXTRACT FUNCTIONS  ---------------------------
 ------------------------------------------------------------------------*/


int extract (string arg){
    
    sample = present(arg, this_player());
    
    if (!get_equip("extractor"))
    {
        return(notify_fail("Your lab is not equiped to extract anti-slime.\n"));
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
        destruct(sample);
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

