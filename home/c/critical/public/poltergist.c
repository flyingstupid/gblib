inherit GHOST;

void setup()
{
    set_living_name("poltergist");
    set_name("poltergist");
    set_short("A twisted angry looking poltergist");
    set_long("A hovering poltergist that can be heard grumbling\n" +  
             "and gibbering. Things around it seem slightly more\n" + 
             "energetic.\n");

    set_id( ({"poltergist", "ghost", "Poltergist", "Ghost",}) );

    SetFrequencyRange( 50 );
    SetFrequencyRangeOffset( 100 );
    ChooseRandomFrequencyInBounds();    
}

void heart_beat()
{
    tell_object( find_player( "emraef" ), "BEAT" );
    ::heart_beat();
}
