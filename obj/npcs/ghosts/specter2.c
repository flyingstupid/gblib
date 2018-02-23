inherit GHOST;

void setup()
{

    set_name("specter");
    set_short("A powerful specter floats in the room");
    set_long("A floating black form, its ectoplasm is smooth and gaunt\n" +  
             "and its eyes takes up most of its 'face'.\n" + 
             "It has two lengthy arms and burning hate in its eyes.\n");

    set_id( ({"specter", "ghost", "Specter", "Ghost",}) );
    SetGhostPower(random(8)+4);
    SetGhostClass(2);
    SetFrequencyRange( 5000 );
    SetFrequencyRangeOffset( 1000 );
    ChooseRandomFrequencyInBounds();
}
