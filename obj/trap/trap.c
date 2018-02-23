inherit OBJECT;

void ThrowTrapAtGhost( object ob );
int ThrowTrap( string arg );
int getTrapedGhostID();
void setTrapedGhostID( int ID );
string CheckTrap( );
void setTrapFull(int num);


int fullTrap;
int trapedGhostID;

void create()
{
	::create();
    set_id(({"trap", "ghosttrap", "Trap", "standard"}));
    set_short("A Standard Ghost Trap");
    set_long("The standard ghost trap for ghostbusters.\n");
    fullTrap=0;
	setValue(10000);
}

string query_long()
{
    return ::query_long() + "\n" + CheckTrap();
}

int getTrapedGhostID()
{
    return trapedGhostID;
}

void setTrapedGhostID( int ID ) 
{
    trapedGhostID=ID;
}

int IsFull()
{
    return fullTrap;
}

void init()
{
    add_action( "throw", "throw" );
}


int throw( string arg )
{
    object ob;
    string target;

    if( !arg || arg == "" )
    {
        write("SYNTAX: throw <target>\n");
        return 1;
    }

    if( IsFull() )
    {
        tell_object( this_user(), "This trap is full buddy.\n" );
        return 1;
    }

    target = arg;

    ob = present( target, environment( this_user() ) );

    if( !ob )
    {
        tell_object( this_user(), "There is no " + target + " present.\n");
    }
    else if( !ob->IsGhost() )
    {
        tell_object( this_user(), "Why would waste a throw on a " + target +
"?\n");
    }
    else
    {
        ThrowTrapAtGhost( ob );
    }

    return 1;
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
		
	if( this_user()->CheckForStatus( "broken_arm") )
		skillCheckDiff += 30;


        write("You wind up an underhanded throw at the ghost!\n");
        output = sprintf( "Making throw test at diff %s[%s%d%s]%s \n", "", "",
                        skillCheckDiff, "", "" );
        write(output);
    if( ob->IsCaptured() )
    {
        
        if(this_user()->DoSkillRoll("throw", skillCheckDiff) > 0)
        {
                
                tell_room( environment( this_user() ),this_user()->query_cap_name()  +  " throws a trap at " + ob->query_cap_name()  + " trapping it inside.\n", environment() );
                trapedGhostID=ob->GetGhostID();
                tell_object( environment(), "YOU GOT HIM!\n");
                destruct( ob );
                fullTrap=1;
                this_object()->set_long("The standard ghost trap for ghostbusters.\n");
				if(wizardp(this_player()))
                this_object()->set_long(this_object()->get_long() + "GhostID:"+ getTrapedGhostID() +"\n");
        }
        else
        {
                        
			tell_room( environment( environment() ), capitalize(
            environment()->query_cap_name() ) +  " throws a trap at " + ob->query_cap_name()  + " and MISSES.\n", environment() );
            tell_object( environment(), "You throw the trap and it lands short!\n");
			this_object()->move(environment(this_player()));	
        }

                

    }
    else
    {   
        tell_object( this_user(), "You can't throw a trap at a ghost who isnt
contained!\n");
    }
}

string CheckTrap( )
{
    if( IsFull() )
    {
        return "The trap's red light is blinking and is smoking slightly.\n";
    }
    else
    {
        return "The light is green the trap is clean.\n";
    }
}


void setTrapFull(int num)
{
	fullTrap=num;
}
