inherit "/std/user/gb_mobile.c";

/*Command Handlers*/
int execute_movement(string verb, string arg);
int execute_ghost_movement(string verb, string arg);
int execute_commandFromPath( string verb, string arg );

/*Functions Descriptions*/
void SetCorpID( string ID );
string GetCorpID();

/** Bladder Functions */
void SetBladder(int val);
int GetBladder();

/** Skill functions */
void set_skill( string skillName, int skillValue );
mapping get_skills();
int get_skill( string skillName );
int DoSkillRoll(string skill, int diff);
void DoSkillXp(string skill);

/** stat functions */
void set_stat( string statName, int statValue );
int get_stat( string statName );
mapping get_stats();

/** Health functions */
void set_health( int newHealth );
int get_health();
void SetHealth( int newHealth );
int GetHealth();
void CauseDamage( int damageAmount );
void HealDamage( int healAmount );


/** Job functions */
array get_currentJob();
void set_currentJob(array ghostIDs,string jobNPC, int bid);

/** Research functions */
int GetResearchTotal();
void SetResearchCurrent(int current);
void SetResearchTotal(int total);
int GetResearchCurrent();

/** combat functions */
int ApplyHit( object HitData );
void ApplyStatusEffects( mixed *newStatus );
void CauseStatus_knockdown();


/***
 * Instance Variables 
 ***/
mapping playerSkills;
mapping playerStats;
int maxHealth;
int health;
array currentJob;
int researchTotal;
int researchCurrent;
string corpID;
int bladder;
mapping statuses;

//
// Command Handling
//

int executeCommandFromPath( string verb, string arg );

mixed process_input(string commandLine)
{
    string verb, args;
    int returnVal;

    // IF there is no command dont continue
    if( commandLine == 0 || commandLine == "" )
        return 1;

    if( sscanf( commandLine, "%s %s", verb, args ) != 2 )
        verb = commandLine;
    
    if( sscanf( alias_parse(verb, args), "%s %s", verb, args ) != 2 ) 
        verb = alias_parse(verb, args);

    if( args == "" ) 
        args = 0;

    // Makes matching easier
    verb = lower_case( verb );
   
    // Command water fall
    if( returnVal = execute_movement( verb, args ) );
    else if( !catch{ load_object( SOUL_D ); } && returnVal = SOUL_D->request_emote( verb, args ) );
    else if( !catch{ load_object( CHAN_D ); } && returnVal = CHAN_D->snd_msg( verb, query_name(), args ) );
    //else if( returnVal = execute_objectCommand( player, verb, args ) );
    else if( returnVal = execute_commandFromPath( verb, args ) );

    if( returnVal == 2 )
    {
        tell_object( this_object(), sprintf( "Whoa! slow down gotta wait %2.2f more seconds.\n", (float)query_time_left_to_wait() / 1000.0 ) );
    }

    if( returnVal == 0 )
    {
        return commandLine;
    }

    return returnVal;
}

/**
 * Checks the players path for a matching command file then executes that command
 *
 * @param verb - command that was called
 * @param arg - additional arguments to the command
 *
 * @return int - 1 if this function handled the command
 */
int execute_commandFromPath( string verb, string arg )
{
    string *path = query_path();
    string *cmds;
    object command;
    int returnValue, i, err;


    cmds = allocate(0);

    for( i = 0; i < sizeof( path ); ++i )
    {
        if( file_exists(path[i] + verb + ".c" ) )
        {
            cmds += ({ path[i] + verb });
        }
    }
    
    if( sizeof( cmds ) > 0 )
    {
        i = 0;
        while(returnValue <= 0 && i < sizeof(cmds))
        {
            err = catch(command = load_object(cmds[i]));
        
            if(err)
            {
                write("Error: Command " + verb + " non-functional.\n");
                write(err);
                i++;
                continue;
            }

            if( !has_to_wait( command->query_wait_type( arg ) ) )
            {
                returnValue = command->main(arg);
                if( command && returnValue > 0 )
                {
                    command->issue_wait_timer( this_object(), arg );
                }
            }
            else
            {
                returnValue = 2;
            }
            i++;
        }
    
        return returnValue;
    }
    return 0;
}

/**
 * Checks the environment of the player for an exit that matches 'verb'
 *
 * @param player - player that issued this command
 * @param verb - command that was called
 * @param arg - additional arguments to the command
 *
 * @return int - 1 if this function handled the command
 */
int execute_movement(string verb, string arg)
{
    object env;
    string tmp, custom;
    int isWiz;

    env = environment( this_object() );

    if( !env ) 
        return 0;

    /*  RWL : Removed Street movement for the time being
    if( is_a( STREETS, env ) )
    {
        return execute_street_movement( player, verb, arg, env );
    }
    */

    isWiz = wizardp( this_object() );

    if( !env->valid_exit( verb ) )
    {
        if( isWiz || is_a( GHOST, this_object() ) )
        {
            return execute_ghost_movement( verb, arg );
        }
        return 0;
    }

    if( !moveAllowed( env->query_exit( verb ) ) )
        return 0;
    
    if( !isWiz && has_to_wait( MOVE_WAIT_TIME_TYPE ) )
        return 2;

    if( !isWiz && GetPosition() != STAND )
    {
        tell_object( this_object(), "You should stand up first.\n" );
        return 1;
    }

    if( !isWiz && env->query_door_state( verb ) > 1 )
    {
        tell_room( env, query_cap_name() + " trys to go " + verb + " but the closed door has other ideas." + "\n", this_object() );
        tell_object( this_object(), "You bump into a closed door trying to go " + verb + ".\n" );
        return 1;
    }

    // Tell the room we are entering that we have
    if( isWiz )
    {
        custom = query_env("move_in");
        if( custom )
        {
            tmp = custom;
            tmp = replace_string( tmp, "$N", query_cap_name() );
            tell_room( env->query_exit(verb), capitalize(tmp) + "\n", this_object() );
        }
    }
    else
    {
        tell_room( env->query_exit( verb ), query_cap_name() + " has entered the room.\n", this_object() );
    }
            
    // Tell the room we are in that we are leaving
    if( isWiz )
    {
        custom = query_env( "move_out" );            
        if( custom )
        {
            tmp = custom;
            tmp = replace_string(tmp, "$N", query_cap_name());
            tmp = replace_string(tmp, "$D", verb);
            tell_room( env, capitalize(tmp) + "\n", this_object() );
        }
    }
    else
    {
        tell_room( env, query_cap_name() + " leaves through the " + verb + " exit.\n", this_object() );
    }

    // Tell the player that the move happend
    tell_object( this_object(), "You move to " + environment(this_object())->query_exit(verb)->query_short() + ".\n\n" );

    move(environment(this_object())->query_exit(verb));

    set_wait_timer( MOVE_WAIT_TIME, MOVE_WAIT_TIME_TYPE );

    return 1;
}


/**
 * Checks the environment of the player for an exit that matches 'verb'
 *
 * @param player - player that issued this command
 * @param verb - command that was called
 * @param arg - additional arguments to the command
 *
 * @return int - 1 if this function handled the command
 */
int execute_ghost_movement(string verb, string arg)
{
    object env;

    env = environment( this_object() );

    if( !env ) 
        return 0;

    if( !env->valid_ghostExit( verb ) )
        return 0;
    
    if( !moveAllowed( env->query_ghostExit( verb ) ) )
        return 0;
    
    if( has_to_wait( MOVE_WAIT_TIME_TYPE ) )
        return 2;

    if( !wizardp( this_object() ) && GetPosition() != STAND )
    {
        tell_object( this_object(), "You should stand up first.\n" );
        return 1;
    }

    tell_room( env->query_ghostExit( verb ), query_short() + env->query_ghostEnterString( verb ) + "\n", this_object() );

    tell_room( env, query_short() + env->query_ghostExitString( verb ) + "\n", this_object() );
            
    // Tell the player that the move happend
    tell_object( this_object(), "You move to " + env->query_ghostExit( verb )->query_short() + ".\n\n" );

    move( env->query_ghostExit(verb) );

    set_wait_timer( MOVE_WAIT_TIME, MOVE_WAIT_TIME_TYPE );

    return 1;
}

mixed process_input_OLD(string commandLine)
{
    int commandReturn;
    string verb;
    string args;

    commandLine = TERMINAL_D->strip_unsafeAnsi(commandLine);

    if( sscanf( commandLine, "%s %s", verb, args ) != 2 )
    {
        verb = commandLine;
        args = "";
    }

    if( sscanf( alias_parse(verb, args), "%s %s", verb, args ) != 2 ) 
    {
        verb = alias_parse(verb, args);
    }

    commandReturn = executeCommandFromPath(verb, args);

    if( commandReturn )
    {
        return commandReturn;
    }

//    return COMMAND_D->execute_command( this_object(), commandLine );
    return 0;
}

int executeCommandFromPath( string verb, string arg )
{
    string *path = query_path();
    string *cmds;
    object command;
    int returnValue, i, err;

    cmds = allocate(0);

    for( i = 0; i < sizeof( path ); ++i )
    {
        if( file_exists(path[i] + verb + ".c" ) )
        {
            cmds += ({ path[i] + verb });
        }
    }
    
    if( sizeof( cmds ) > 0 )
    {
        i = 0;
        while(returnValue <= 0 && i < sizeof(cmds))
        {
            err = catch(command = load_object(cmds[i]));
        
            if(err)
            {
                write("Error: Command " + verb + " non-functional.\n");
                write(err);
                i++;
                continue;
            }

            if( !has_to_wait( command->query_wait_type( arg ) ) )
            {
                returnValue = command->main(arg);
                if( command && returnValue > 0 )
                {
                    command->issue_wait_timer( this_object(), arg );
                }
            }
            else
            {
                returnValue = 2;
            }
            i++;
        }
    
        return returnValue;
    }
    return 0;
}


//-------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------

/**
 * called from the create of object.c to setup this object
 */
void setup()
{
    ::setup();

    // setup variables if they are missing
    if( !maxHealth ) maxHealth = 100;
    if( !health ) health = maxHealth;
    if( !playerSkills ) playerSkills = allocate_mapping( 0 );
	if( !playerSkills ) playerStats = allocate_mapping( 0 );
    if( !corpID ) corpID = "GBA";
    if( !bladder ) bladder = 0;
    /*if( !statuses )*/ statuses = allocate_mapping( 0 );
    set_heart_beat( 1 );
}

/**
 * Sets the corp ID string for this Player
 *
 * @param ID - the new corp ID
 */
void SetCorpID( string ID )
{
    corpID = ID;
}

/**
 * Gets the corp ID string for this Player
 *
 * @return string - the players corp ID
 */
string GetCorpID()
{
    return corpID;
}


/* Setting the Bladder */
void SetBladder(int val)
{
	bladder=val;
}

/* Getting the Bladder */
int GetBladder()
{
	return bladder;
}


/**
 * Set a skill by skillname
 *
 * @param[in] skillName - Key in the mapping where the skill should be set
 * @param[in] skillValue - value the skill should be set to
 */
void set_skill( string skillName, int skillValue )
{
    if( skillValue == 0 )
    {
        if( !undefinedp( playerSkills[skillName] ) )
        {
            map_delete( playerSkills, skillName );
        }

        return;
    }
    playerSkills[skillName] = skillValue;
}

int get_skill( string skillName )
{
    if( undefinedp( playerSkills[skillName] ) )
    {
        return 0;
    }

    return playerSkills[skillName];
}

mapping get_skills()
{
    mapping a;
    a = playerSkills;

    return a;
}

void set_stat( string statName, int statValue )
{
    playerStats[statName] = statValue;
}

int get_stat( string statName )
{
    if( undefinedp( playerStats[statName] ) )
    {
        return 0;
    }

    return playerStats[statName];
}

mapping get_stats()
{
    mapping a;
    a = playerStats;

    return a;
}


void set_health( int newHealth )
{
    if( newHealth > maxHealth )
    {
        health = maxHealth;
    }
    else if( newHealth < 0 )
    {
        health = 0;
    }
    else
    {
        health = newHealth;
    }
}

int get_health()
{
    return health;
}

void heart_beat()
{
    if( get_health() == 0 )
    {
        move( "/areas/morgue/morgue.c" );
    }

    if( get_health() < maxHealth )
    {
        HealDamage( 1 );
    }
}

array get_currentJob()
{
    return currentJob;
}

void set_currentJob(array ghostIDs,string jobNPC, int bid)
{
    currentJob=({ghostIDs,jobNPC, bid});
}

int GetResearchTotal()
{
	return researchTotal;	
}

int GetResearchCurrent()
{
	return researchCurrent;	
}

void SetResearchTotal(int total)
{
	researchTotal=total;
}

void SetResearchCurrent(int current)
{
	researchCurrent=current;	
}

int DoSkillRoll(string skill, int diff)
{
	int d100;
	int skillValue;

	if( undefinedp( diff ) )
	{
        diff=0;
	}
	
	d100=random(100)+1;
	skillValue = this_user()->get_skill(skill) - diff;
	
	if( d100 <= skillValue )
	{
		DoSkillXp(skill);
	}

    return d100 - skillValue;
}

void DoSkillXp(string skill)
{
	int firstD100;	
	int secondD100;
	int skillValue;
	
	skillValue=this_user()->get_skill(skill);
	
	firstD100=random(100)+1;
	secondD100=random(100)+1;
	if(firstD100 > skillValue && secondD100 > skillValue)
	{
		this_player()->set_skill(skill, skillValue+1); 
		write("%^GREEN%^You believe you've learned something about " + skill + "%^RESET%^.\n");
	}
	
}


/**
 * Causes damage to the player.
 *
 * This cannot be used to heal the player any value 0 or less is ignored.
 *
 * @param[in] damageAmount - amount to subtract from the players current health.
 */
void CauseDamage( int damageAmount )
{
    if( undefinedp( damageAmount ) ||
        damageAmount <= 0 )
    {
        return;
    }

    set_health( get_health() - damageAmount );
}

/**
 * Heals the player an amount
 *
 * This cannot be used to damage the player any value 0 or less is ignored.
 *
 * @param[in] healAmount - the amount to heal by
 */
void HealDamage( int healAmount )
{
    if( undefinedp( healAmount ) ||
        healAmount <= 0 )
    {
        return;
    }

    set_health( get_health() + healAmount );
}

/**
 * Called to Apply a hit to this object.
 *
 * This is the main call for combat.  All combat hits should go through
 * this call allowing objects to handle hits differently
 * 
 * @param[in] hitData - the data object for the hit.  This needs to be cleaned
 *                      by this function.
 *
 * @return int - Non zero if the hit was handled.  0 value indicates that the
 *               Hit was not handled and the hit data was not cleaned.
 */
int ApplyHit( object HitData )
{
    if( undefinedp( HitData ) ||
        !is_a( HITDATA, HitData ) )
    {
        return 0;
    }

    CauseDamage( HitData->GetDamage() );

    ApplyStatusEffects( HitData->GetStatusEffects() );

    // our responsibility to clean up the hit Data.
    destruct( HitData );

    return 1;
}	


void ApplyStatusEffects( mixed *newStatuses )
{
    if( !newStatuses )
        return;

    write( "Applying status Effects" );
    foreach( mixed *SE in newStatuses )
    {
        if( !call_other( this_object(), "AddStatus_" + SE[0], ({ SE[1], SE[2] }) ) )
        {
            statuses[ SE[0]] = ({ SE[1], SE[2] });
        }
        call_other( this_object(), "CauseStatus_" + SE[0] );
    }
}

void ClearAllStatuses()
{
    statuses = allocate_mapping( 0 );
}

void CauseStatus_knockdown()
{
    say( query_cap_name() + " GOT KNOCKED TO THE GROUND!\n" );
}

mapping get_statuses()
{
    return copy(statuses);
}

void ClearStatus( string status )
{
    if( !undefinedp( statuses[ status ] ) )
    {
        map_delete( statuses, status );
    }
}

int CheckForStatus( string status )
{
    return !undefinedp( statuses[ status ] );
}
