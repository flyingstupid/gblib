//
//  /obj/research/antislime.c
//  GB Mud
//


inherit OBJECT;

/* FUNCTION PROTOTYPES */
int get_potency();
void set_potency(int vaule);


string get_enhancement();
void set_enhancement(string value);

/* GLOBAL VARIABLES */
int potency;
string enhancement;



void create()
{
    ::create();
    
    set_id(({"anti-slime", "antislime"}));
    set_short("anti-slime");
    set_long ("A shimmering jar of anti-slime");

}


int get_potency()
{
    return potency;
}
void set_potency(int vaule)
{
    potency = vaule;
}


string get_enhancement()
{
    return enhancement;
}
void set_enhancement(string value)
{
    enhancement = value;
}
