inherit GHOST;

void setup()
{
    ::setup();

    set_name("newbie ghost");
    set_short("A weak looking ghost floats in the room");
    set_long("A strange floating ghost that just appears weak some how");
    set_id( ({"newbie", "ghost", "Newbie", "Ghost",}) );
    SetGhostPower(random(4)+1);
    SetGhostClass(random(3)+1);
    SetFrequencyRange( 500 );
    SetFrequencyRangeOffset( 100 );
	SetGhostID(100000);
    ChooseRandomFrequencyInBounds(); 
}