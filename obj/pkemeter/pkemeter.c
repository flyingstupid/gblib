//
//   /obj/pkemeter/pkemeter.c
//

inherit OBJECT;

/** function decs */
int MakeReading( );
int is_pkeMeter();
int ghostPresent();

/** object variables */
int reading;
int playerskill;
object player;
int ready;

void create()
{
        ::create();
    set_id( ({ "PKE", "Meter", "pke", "meter", }) );
    set_short("A PKE Meter");
    set_long("The standard PKE meter for ghostbusters.\n");
    reading = 0;
    ready = 1;
        setValue(50000);
}

void init()
{
    add_action( "StartReading", "scan" );
}

int StartReading( string arg )
{
    if (!ready){
        tell_object( this_user(), "You have not completed the previous scan
yet.\n" );
        return 1;
    }
 /*   
        Removed for invisible ghost addition
        -Critical

 if (!ghostPresent()){
        tell_object( this_user(), "There don't seem to be any paranormal
entities in this room.\n" );
        return 1;
                }

                else 

*/
        tell_object( this_user(), "You are start scanning for PKE valances.\n");
        say(this_user()->query_cap_name()  + " starts scanning with a PKE meter.\n" );
        call_out("MakeReading", 3);
        ready = 0;
        return 1;
    
          
}

int is_pkeMeter()
{
    return 1;
}

void heart_beat()
{
    MakeReading();
    set_heart_beat( 0 );
}

int MakeReading( )
{
   
    int ghostFrequency;
    int ghostRange;
    int ghostRangeOffset;
    int scanRoll;
    int scanRange;
    int guessFrequency;
    int xnum;
    
        
    object *obArray = all_inventory( environment( environment( this_object() )));
    object player = this_player();
    
    if(!ghostPresent())
    {
	 	write("Your readings come back negative for PK energies.\n");   
	    return 1;
    }
    
    
    for( int i = 0; i < sizeof( obArray ); i++ )
    {
        if( !inherits( GHOST, obArray[i] ) )
        {
            continue;
        }
        
        if( ghostRange < obArray[i]->GetFrequencyRange() )
        {
            ghostFrequency = obArray[i]->GetFrequency();
            ghostRange = obArray[i]->GetFrequencyRange();
            ghostRangeOffset = obArray[i]->GetFrequencyRangeOffset();
        }
    }

        
    playerskill = player->get_skill("scan");
    scanRoll = playerskill+random( 25 )+1;
    //write ("the roll is " + scanRoll + "\n"); 
    
    if( scanRoll > 90 )
    {
        scanRange = ghostRange * 0.05;
       // write ("pass one\n");
    }
    else if( scanRoll > 70 )
    {
        scanRange = ghostRange * 0.1;
        //write ("pass two\n");
    }
    else if( scanRoll > 50 )
    {
        scanRange = ghostRange * 0.2;
       // write ("pass three\n");
    }
    else if( scanRoll > 40 )
    {
        scanRange = ghostRange * 0.4;
        //write ("pass four\n");
    }
    else if( scanRoll > 30 )
    {
        scanRange = ghostRange * 0.6;
        xnum = random(100);
        if (xnum >80){
            //write("minor fail!\n");
            this_player()->DoSkillXp("scan");
        }
    }
    else if( scanRoll > 20 )
    {
        scanRange = ghostRange * 0.8;
        xnum = random(100);
        if (xnum >50){
           // write ("fail!\n");
            this_player()->DoSkillXp("scan");
        }
    }
    else
    {
        scanRange = ghostRange * 1.0;
        //write ("major fail!\n");
        xnum = random(100);
        if (xnum >20){
            this_player()->DoSkillXp("scan");
        }
        
    }
    
    guessFrequency = ( ( random(2) == 1 ? 1 : -1 ) * random( scanRange ) ) +
ghostFrequency;
    tell_object( environment( this_object() ), "Your readings tell you the ghost is at frequency " + guessFrequency  + " plus or minus " + to_int( scanRange ) +".\n" );
    ready = 1;
    return 1;
}

int ghostPresent(){
    object *obArray = all_inventory( environment( environment( this_object() )
));
     int i = 0;
    
    while (i < sizeof( obArray ))
    {
        if( inherits( GHOST, obArray[i] ) )
        {
            return 1;
        }
        i++;
    }
    return 0;
}
