inherit GHOST;

void setup()
{

    set_name("banshee");
    set_short("A banshee floats in the room");
    set_long("A floating thin woman ectoplasm is shaded\n" +  
             "and its mouth twists in horror and her expression.\n" + 
             "is one of terror and anger.\n");

    set_id( ({"banshee", "ghost", "Banshee", "Ghost",}) );
    SetGhostPower(random(5)+1);
    SetGhostClass(5);
    SetFrequencyRange( 150 );
    SetFrequencyRangeOffset( 50 );
    ChooseRandomFrequencyInBounds();
}

