//   /std/user/gb_mobile.c

inherit "/std/user/mobile.c";

nosave int issuedCommandTime;
nosave int waitTime;
nosave int waitTimeType;
int cash;
nosave string positionPost;
nosave int position;
nosave object furniture;

nosave mixed *validWearLocations;
nosave mapping wearLocations;


/* Position & Furniture Commands  */
int GetPosition();
string GetPositionPost();
void SetPosition( int pos );
void SetPositionPost( string position );
object GetFurniture();
void SetFurniture(object _furniture);


void set_cash( int tempCash );
int get_cash();
string get_cash_get();
int query_issued_command_time();
int query_wait_time();
int query_wait_time_type();
void set_issued_command_time( );
int has_to_wait( int waitType );
void set_wait_timer( int _waitTime, int _waitTimerType );
int query_time_left_to_wait( );

/** combat functions */
int ApplyHit( object HitData );

/** Wear Location functions **/
mapping get_wear_location_data();
int remove_object_from_slots( object ob );
int set_object_in_slot( object ob, string loc );
object get_object_in_slot( string testLoc );
int is_valid_wear_loc( string testLoc );

void create()
{
    ::create();
    set_wait_timer( 0, -1 );
    
    if( undefinedp( _x ) ) _x = 0;
    if( undefinedp( _y ) ) _y = 0;
    if( undefinedp( _z ) ) _z = 0;
    
    SetPosition( STAND );
    
    enable_commands();

    wearLocations = ([ "head":0,
                       "neck":0,
                       "l_arm":0,
                       "r_arm":0, 
                       "body":0, 
                       "waist":0, 
                       "legs":0, 
                       "r_foot":0, 
                       "l_foot":0, 
                       "about":0, 
                       "back":0, 
                       "uniform":({ "body", "legs" }), // Takes up body and waist slots
                       "eyes":0, 
                       "l_ear":0, 
                       "r_ear":0,
                       "l_wrist":0,
                       "r_wrist":0,
                       "r_hand":0,
                       "l_hand":0,
                       "r_weapon":0,
                       "l_weapon":0
                       ]);
}

//----------------------------------------------------------------------
mapping get_wear_location_data()
{
    return copy( wearLocations );
}

//----------------------------------------------------------------------
int is_valid_wear_loc( string testLoc )
{
    if( undefinedp( wearLocations[testLoc] ) ) {
        return 0;
    }

    return 1;
}


//----------------------------------------------------------------------
object get_object_in_slot( string testLoc )
{
    mixed slot;
    int i;

    if( !is_valid_wear_loc( testLoc ) ) {
        return 0;
    }

    slot = wearLocations[ testLoc ];

    if( arrayp( slot ) ) {
        for( i = 1; i < sizeof( slot ); i++ ) {
            if( wearLocations[ slot[0] ] != wearLocations[ slot[i] ] ) {
                return 0;
            }
        }

        return wearLocations[ slot[0] ];
    }

    return slot;
}


//----------------------------------------------------------------------
int set_object_in_slot( object ob, string loc )
{
    mixed slot;
    int i;

    if( !is_valid_wear_loc( loc ) ) {
        return 0;
    }

    remove_object_from_slots( ob ); 


    slot = wearLocations[ loc ];


    if( arrayp( slot ) ) {
        
        for( i = 0; i < sizeof( slot ); i++ ) {
            wearLocations[ slot[i] ] = ob;
        }
        
        ob->equipped_to_location( loc );
        
        return 1;
    }

    wearLocations[ loc ] = ob;
    ob->equipped_to_location( loc );
    return 1;
}


//----------------------------------------------------------------------
int remove_object_from_slots( object ob )
{
    int i;
    string *locs;
    int removed = 0;

    if( ob == 0 ) {
        return 0;
    }

    locs = keys( wearLocations );

    for( i = 0; i < sizeof( locs ); ++i ) {
        if( wearLocations[locs[i] ] == ob ) {
            wearLocations[locs[i] ] = 0;
            removed = 1;
        }
    }

    if( removed ) {
        ob->removed_from_slots();
    }

    return removed;
}



void set_cash( int tempCash )
{
    cash = tempCash;
}

int get_cash()
{
    return cash;
}

string get_cash_string()
{
    return sprintf( "%d.%2.2d", get_cash()/100, get_cash()%100 );
}

int query_issued_command_time()
{
    return issuedCommandTime;
}

int query_wait_time()
{
    return waitTime;
}

int query_wait_time_type()
{

    return waitTimeType;
}

void set_issued_command_time( )
{
    issuedCommandTime = mtime();
}

void set_wait_time( int _waitTime )
{
    waitTime = _waitTime;
} 

void set_wait_time_type( int _waitTimeType )
{
    waitTimeType = _waitTimeType;
}

int has_to_wait( int waitType )
{
    if( !waitType || waitType == -1 )
    {
        return 0;
    }
    
    
    if( waitType <= query_wait_time_type() )
    {
        return ( mtime() - query_issued_command_time() ) < waitTime;
    }
    
    return 0;
}

int query_time_left_to_wait( )
{
    int timeLeft = waitTime - ( mtime() - query_issued_command_time() );
    
    if( timeLeft < 0 )
    {
        return 0;
    }
    
    return timeLeft;
}

void set_wait_timer( int _waitTime, int _waitTimeType )
{
    if( _waitTime > 0 && _waitTimeType > 0 )
    {
        waitTime = _waitTime;
        waitTimeType = _waitTimeType;
        
        set_issued_command_time();
    }
}

string query_prompt( string prompt )
{
    string timeLeft = "";
    float secondsLeft = query_time_left_to_wait() / 1000.0;
    
    timeLeft = sprintf( "%2.2f", secondsLeft );
    
    prompt = ::query_prompt( prompt );
    prompt = replace_string( prompt, "$W", secondsLeft > 0 ? ( "[" + timeLeft + "]" ) : "" );
    prompt = replace_string( prompt, "%W", secondsLeft > 0 ? timeLeft : "" );
    prompt = replace_string( prompt, "%w", timeLeft );
    
    return prompt;
}


/*    Position functions! */
int GetPosition()
{
    return position;	
}

string GetPositionPost()
{
    return positionPost;
}

void SetPosition( int pos )
{
    
    switch( pos )
    {
        case STAND:
            SetPositionPost( "" );
            break;
        case KNEEL:
            SetPositionPost( " is kneeling." );
            break;
        case SIT:
            SetPositionPost( " is sitting on the floor." );
            break;
        case LAY:
            SetPositionPost( " is laying on the floor." );
            break;
        case REST:
            SetPositionPost( " is laying on the floor resting." );
            break;
        default:
            SetPositionPost( "" );
            break;
    }
    
    position = pos;
}

void SetPositionPost( string position )
{
    positionPost = position;	
}

object GetFurniture()
{
    return furniture;
}

void SetFurniture(object _furniture)
{
    furniture=_furniture;
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
    return 0;
}


////////////////////////////////////////////////////
// Command Handling
//

int executeCommandFromPath( string verb, string arg );
int execute_movement(string verb, string arg);
int execute_ghost_movement(string verb, string arg);
int execute_commandFromPath( string verb, string arg );

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
    else if( !catch{ load_object( SOUL_D ); } && returnVal =
            SOUL_D->request_emote( verb, args ) );
    else if( !catch{ load_object( CHAN_D ); } && returnVal = CHAN_D->snd_msg(
                                                                             
                                                                             verb, query_name(), args ) );
    //else if( returnVal = execute_objectCommand( player, verb, args ) );
    else if( returnVal = execute_commandFromPath( verb, args ) );
    
    if( returnVal == 2 )
    {
        tell_object( this_object(), sprintf( "Whoa! slow down gotta wait %2.2f
                                            more seconds.\n",
                                            (float)query_time_left_to_wait() / 1000.0 ) );
    }
    
    if( returnVal == 0 )
    {
        return commandLine;
    }
    
    return returnVal;
}

/**
 * Checks the players path for a matching command file then executes that
 command
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
    string nextRoomName;
    object nextRoom;
   
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
    
    nextRoomName = env->query_exit(verb) + ".c";
    nextRoom = find_object(nextRoomName);
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
        tell_object( this_object(), "You bump into a closed door trying to go "+ verb + ".\n" );
        return 1;
    }
    
    //this will inhibit ghosts from moving into ghost free rooms
    
    if (is_a( GHOST, this_object() ) && (!nextRoom->get_ghost_ok())){
        return 0;
    }
    // Tell the room we are entering that we have
                
    if( isWiz )
    {
        custom = query_env("move_in");
        if( custom )
        {
            tmp = custom;
            tmp = replace_string( tmp, "$N", query_cap_name() );
            tell_room( env->query_exit(verb), capitalize(tmp) + "\n",
                      this_object() );
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
    
    tell_room( env->query_ghostExit( verb ), query_short() +
              env->query_ghostEnterString( verb ) + "\n", this_object() );
    
    tell_room( env, query_short() + env->query_ghostExitString( verb ) + "\n",
              this_object() );
    
    // Tell the player that the move happend
    tell_object( this_object(), "You move to " + env->query_ghostExit( verb
                                                                      
                                                                      )->query_short() + ".\n\n" );
    
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
