//
//  /chipmunk.c
//  GBMud
//




inherit GHOST;

void set_value();
int get_value();

int value;

void setup()
{
    ::setup();
    
    set_name("chipmunk");
    set_short("a beaten and battered ghost os a chipmunk rustles under some leaves.");
    set_long("Missing clumps of fur and one eyeball, this little\n" +  
             "ghost of a rident is only a shadow of it's adorable\n" + 
             "self.\n");
    
    set_id( ({"chipmunk", "ghost", "Chipmunk", "Ghost",}) );
    SetGhostPower(random(1)+1);
    SetGhostClass(1);
    SetFrequencyRange( 150 );
    SetFrequencyRangeOffset( 50 );
    ChooseRandomFrequencyInBounds(); 
}


void set_value()
{
    value = power * 10 * (random[3]+1);
}
int get_value()
{
    return value;
}