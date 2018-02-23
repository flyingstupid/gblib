inherit OBJECT;

/** Function Decs */
int GetPower( );
void ShootObject( object ob );
void ShootGhost( object ob );
int adjust( string arg );
void captured_heart_beat();
string DisplayPower( );
int SkillCheckShot( object ob );

/** object variables */
int frequency;
int freqencyThreshold;
int maxPower;
int currentPower;
object lockedGhost;
int holdTickCounter;
int rechargeTickCounter;

int costToShoot;
int costToHold;
int ticksPerHoldCost;
int rechargeAmount;
int ticksPerCharge;



/**
 * Function is called by the driver when the object is created
 */
void create()
{
    // THIS NEEDS TO BE HERE!
    ::create();

    set_id(({"proton", "pack", "proton pack"}));
    set_short("A Standard Proton Pack");
    set_long("The standard proton pack for ghostbusters.\n");
    frequency = 0;
    freqencyThreshold = 0;
    maxPower = 25;
    currentPower = maxPower;
    costToShoot = 5;
    costToHold = 1;
    ticksPerHoldCost = 1;
    ticksPerCharge = 2;
    rechargeAmount = 4;
	setValue(100000);
    allowedWearLocs = ({"back"});
}

string query_long()
{
    return ::query_long() + "\n" + DisplayPower();
}

void init()
{
    add_action( "shoot", "shoot" );
}


/**
 * function to display the power of this pack to the user
 * 
 * @return string - Display String
 */
string DisplayPower( )
{
    return "The power gage reads: " + GetPower() + ".\n";
}

/**
 * Utiliy function to get the power of this pack
 * 
 * Note this is not a query because this is not just a variable return
 * calculations can be done in this function so it is a get
 *
 * @return int - the amount of power this pack has
 */
int GetPower( )
{
    return currentPower;
}

/**
 * Function to subtract power from the capacitors.  This function will return
 * 0 if there is not enough power and 1 if there was enough power
 *
 * @param[in] amoutn - the amount of power to be removed from the cap
 *
 * @return int - 0 if there wasnt enough power 1 if everything happend ok
 */
int UsePower( int amount )
{
    if( currentPower < amount )
    {
        return 0;
    }

    currentPower -= amount;
    if( query_heart_beat( ) == 0 )
    {
        set_heart_beat( 1 );
    }
 
    return 1;
}

void heart_beat()
{
    if( lockedGhost != 0 )
    {
        captured_heart_beat();
        return;
    }

    rechargeTickCounter--;
    if( rechargeTickCounter <= 0 )
    {
        rechargeTickCounter = ticksPerCharge;
        currentPower += rechargeAmount;
        if( currentPower >= maxPower )
        {
            set_heart_beat( 0 );
            currentPower = maxPower;
        }
    }
}

void captured_heart_beat()
{
    holdTickCounter--;
    if( holdTickCounter > 0 )
    {
        return;
    }
    
    holdTickCounter = ticksPerHoldCost;

    if( UsePower( costToHold ) <= 0 )
    {
        lockedGhost->Released( environment( this_object() ) );
        lockedGhost = 0;
    }
}

/**
 * Command function to shoot things with the pack
 */
int shoot( string arg )
{
    object ob;
    int newFrequency;
    int targetNum;
    string target;

    if( !arg )
    {
        tell_object( this_user(), "SYNTAX:shoot <target> <Frequency>\n" );   
        return 1;
    }

    if( sscanf( arg, "%s %d %d", target, targetNum, newFrequency ) == 3 )
    {
        target += " " + targetNum;
    }
    else if( sscanf( arg, "%s %d", target, newFrequency ) == 2 )
    {
        tell_object( this_user(), "You adjust your proton pack's frequency to " + newFrequency + "\n" );
    }
    else
    {
        tell_object( this_user(), "You should you know how to use one of these? Maybe you should head back to the academy.\n" );
        return 1;
    }

    frequency = newFrequency;
    ob = present( target, environment( this_user() ) );

    if( ob )
    { 
        if( UsePower( costToShoot ) == 0 )
        {
            tell_object( this_user(), "Not enough Power to shoot.  Your capacitor needs to recharge(" + GetPower() + ")\n" );
            return 1;
        }

        if( SkillCheckShot( ob ) )
        {
            if( is_a( GHOST, ob ) )
            {
                ShootGhost( ob );
            }
            else
            {
                ShootObject( ob );
            }

            tell_object( this_user(), "You shoot at " + ob->query_cap_name()+ ".\n" );
            say( this_user()->query_cap_name() + " shoots at " + ob->query_cap_name() + ".\n" );
        }
        else
        {
            tell_object( this_user(), "You miss!\n" );
            say( this_user()->query_cap_name() + " misses!\n" );
        }
    }
    else
    {
        tell_object( this_user(), "There is no " + target + " to shoot at.\n" );
    }

    return 1;
}

/**
 * Function to handle shooting a ghost
 */
void ShootGhost( object ob )
{
    int freqDiffSq;
    int ghostFrq;

    ghostFrq = ob->GetFrequency();

    // Get the difference Squared and compair it agenst our threshold squared.
    freqDiffSq = frequency - ghostFrq ;
    freqDiffSq *= freqDiffSq;


    if( freqDiffSq <= ( freqencyThreshold * freqencyThreshold ) )
    {
        ob->SetCaptured( this_user() );
        lockedGhost = ob;
        tell_object( this_user(), "The light on your protonpack blinks %^BOLD%^GREEN%^green%^RESET%^ as the stream loops around the ghost!  YOU'VE GOT 'IM!\n" );
        say( capitalize(this_user()->query_name()) + "'s beam loops around the ghost!\n" );
    }
    else if( frequency < ghostFrq )
    {
        tell_object( this_user(), "The light on your protonpack blinks %^YELLOW%^yellow%^RESET%^ as the stream seems ineffective.\n" );
        say( capitalize(this_user()->query_name()) + "'s beam seems inefective\n" );
    }
    else if( frequency > ghostFrq )
    {
        tell_object( this_user(), "The light on your protonpack blinks %^BOLD%^CYAN%^blue%^RESET%^ as the stream seems ineffective.\n" );
        say( capitalize(this_user()->query_name()) + "'s beam seems inefective\n" );
    }
}

void ShootObject( object ob )
{

}

int SkillCheckShot( object ob )
{
    int skillCheckDiff;
    string output;

    if( !is_a( GHOST, ob ) )
        return 0;

    skillCheckDiff = ob->GetGhostPower() * 3;
    
    if( this_user()->CheckForStatus( "slimed" ) )
        skillCheckDiff += 10;

    if( this_user()->CheckForStatus( "knockdown" ) )
        skillCheckDiff += 30;
	if( this_user()->CheckForStatus( "broken_arm" ) )
		skillCheckDiff += 30;

    output = sprintf( "Making aim test at diff %s[%s%d%s]%s ", "", "",
skillCheckDiff, "", "" );

    if( this_user()->DoSkillRoll( "aim", skillCheckDiff ) < 0 )
    {
        output += "%^BOLD%^RED%^FAILURE!%^RESET%^\n";
        write( output );
        return 0;
    }

    output += "%^BOLD%^GREEN%^SUCCESS!%^RESET%^\n";

    write( output );

    return 1;
}
