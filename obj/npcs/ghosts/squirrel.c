//
//  /obj/npcs/ghosts/squirrel.c
//  GBMud
//




inherit GHOST;

void set_value();
int get_value();

int verminValue;

void setup()
{
    ::setup();
    
    set_name("squirrel");
    set_short("a previously cute and fuzzy squirrel lurks in the shadows");
    set_long("This furry rodenst was once the possessor of a cute\n" +  
             "and fuzzy tail, but now it is just a grotesque\n" + 
             "etherial spirit of it's former self.\n");
    
    set_id( ({"squirrel", "ghost", "Squirrel", "Ghost",}) );
    SetGhostPower(random(2)+1);
    SetGhostClass(1);
    SetFrequencyRange( 150 );
    SetFrequencyRangeOffset( 50 );
    ChooseRandomFrequencyInBounds(); 
    set_value();
}


void set_value()
{
    verminValue = GetGhostPower() * 10 * (random(3)+1);
}
int get_value()
{
    return verminValue;
}
