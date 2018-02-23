inherit GHOST;

void setup()
{
    ::setup();

    set_name("slimer");
    set_short("A powerful slimer floats in the room");
    set_long("A floating green blob, its ectoplasm is heavily wrinkled\n" +  
             "and its mouth takes up most of its 'face'.\n" + 
             "It has two stubby arms and a massive red tongue.\n");

    set_id( ({"slimer", "ghost", "Slimer", "Ghost",}) );
    SetGhostPower(random(8)+2);
    SetGhostClass(1);
    SetFrequencyRange( 150 );
    SetFrequencyRangeOffset( 50 );
    ChooseRandomFrequencyInBounds();
}
