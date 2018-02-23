inherit GHOST;

void setup()
{

    set_name("specter");
    set_short("A powerful specter floats in the room");
    set_long("A floating green blob, its ectoplasm is heavily wrinkled\n" +  
             "and its mouth takes up most of its 'face'.\n" + 
             "It has two stubby arms and a massive red tongue.\n");

    set_id( ({"specter", "ghost", "Specter", "Ghost",}) );
    SetGhostPower(random(8)+2);
    SetGhostClass(2);
    SetFrequencyRange( 150 );
    SetFrequencyRangeOffset( 50 );
    ChooseRandomFrequencyInBounds();
}
