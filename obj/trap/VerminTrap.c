//
//  /obj/trap/VerminTrap.c
//  GB Mud
//

inherit "/obj/trap/trap.c";

int get_vermin_value();

// Global Variables
int verminValue;

void create()
{
    ::create();
    
    set_id(({"vermin", "vermin trap", "trap", "ghosttrap", "Trap", "standard"}));
    set_short("A vermin ghost trap");
    set_long("A small and old ghost traps, only powerful enough to hold small innocuous ghosts.\n"
             "There is a stamp across the front that reads \"property of GB City\"\n");
    fullTrap=0;
}

void ThrowTrapAtGhost( object ob )
{
    
    int skillCheckDiff;
    string output;
    
    skillCheckDiff = ob->GetGhostPower() * 3;
    
    if( this_user()->CheckForStatus( "slimed" ) )
        skillCheckDiff += 10;
    
    if( this_user()->CheckForStatus( "knockdown" ) )
        skillCheckDiff += 30;
    
    
    write("You wind up an underhanded throw at the ghost!\n");
    output = sprintf( "Making aim test at diff %s[%s%d%s]%s \n", "", "",
                     skillCheckDiff, "", "" );
    write(output);
    if( ob->IsCaptured() )
    {
        
        if(this_user()->DoSkillRoll("throw", skillCheckDiff) > 0)
        {
            
            tell_room( environment( environment() ), capitalize( environment()->query_name() ) +  " throws a trap at " + capitalize( ob->query_name() ) + " trapping it inside.\n", environment() );
            trapedGhostID=ob->GetGhostID();
            tell_object( environment(), "YOU GOT HIM!\n");
            verminValue = ob->get_value();
            write ("You have captured a ghost worth " + verminValue + "dollars\n");
            destruct( ob );
            fullTrap=1;
            this_object()->set_long("The standard ghost trap for ghostbusters.\n GhostID:"+ getTrapedGhostID() +"\n");
        }
        else
        {
            tell_room( environment( environment() ), capitalize( environment()->query_name() ) +  " throws a trap at " + capitalize( ob->query_name() ) + " and MISSES.\n", environment() );
            tell_object( environment(), "You throw the trap and it lands short!\n");
        }
    }
    else
    {   
        tell_object( this_user(), "You can't throw a trap at a ghost who isnt contained!\n");
    }
}

int get_vermin_value()
{
    return verminValue;
}