/* command_d.c
 *
 * Emraef @ GBmud
 * 24-MAY-08
 * Command daemon.
 *
 * Contributors: Emraef
 *
 */

nosave object currentPlayer;
nosave string failString;

mapping objectCommands;

/** Command functions */
int execute_movement(object player, string verb, string arg);
int execute_commandFromPath( object player, string verb, string arg );
int execute_street_movement(object player, string verb, string arg, object env);
int execute_objectCommand( object player, string verb, string arg );
int execute_ghost_movement(object player, string verb, string arg);

/** Helper functions */
void issue_wait_time_err( object player );
object current_player();

void create()
{
    if( undefinedp( objectCommands ) )
    {
        objectCommands = ([
                             "throw"      : ({ TRAP }),
                             "shoot"      : ({ PROTONPACK }),
                             "makereading": ({ PKEMETER }),
                         ]);
    }
}


/**
 * called in the process_input of the player to execute the command
 *
 * @param player - the player from the process_input
 * @commandLine - the input from the player
 *
 * @return mixed - legacy return type to allow process_input to work with add_action
 */
mixed execute_command(object player, string commandLine)
{
    string verb, args;
    int returnVal;

    if( !is_a( MOBILE, player ) )
    {
        return 1;
    }

    currentPlayer = player;

    if( commandLine == 0 || commandLine == "" )
    {
        return 1;
    }

    if( sscanf( commandLine, "%s %s", verb, args ) != 2 )
    {
        verb = commandLine;
    }

    if( sscanf( player->alias_parse(verb, args), "%s %s", verb, args ) != 2 ) 
    {
        verb = player->alias_parse(verb, args);
    }

    if( args == "" )
    {
        args = 0;
    }

    // Lower case the verb so we can match easier
    verb = lower_case( verb );

    if( returnVal = execute_movement( player, verb, args ) );
    else if( !catch{ load_object( SOUL_D ); } && returnVal = SOUL_D->request_emote( verb, args ) );
    else if( !catch{ load_object( CHAN_D ); } && returnVal = CHAN_D->snd_msg( verb, player->query_name(), args ) );
    else if( returnVal = execute_objectCommand( player, verb, args ) );
    else if( returnVal = execute_commandFromPath( player, verb, args ) );

    if( returnVal == 2 )
    {
        issue_wait_time_err( player );
    }


    if( returnVal == 0 )
    {
        if( !failString )
        {
            write( "What?\n" );
        }
        else
        {
            write( failString );
        }
    }

    currentPlayer = 0;
    failString = 0;

    return returnVal;
}


/**
 * Checks the players path for a matching command file then executes that command
 *
 * @param player - player that issued this command
 * @param verb - command that was called
 * @param arg - additional arguments to the command
 *
 * @return int - 1 if this function handled the command
 */
int execute_commandFromPath( object player, string verb, string arg )
{
    string *path = player->query_path();
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

            if( !player->has_to_wait( command->query_wait_type( arg ) ) )
            {
                returnValue = command->main(arg);
                if( command && returnValue > 0 )
                {
                    command->issue_wait_timer( player, arg );
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
int execute_ghost_movement(object player, string verb, string arg)
{
    object env;
    string tmp, custom;

    env = environment( player );

    if( !env ) 
    {
        return 0;
    }

    if( !env->valid_ghostExit( verb ) )
    {
        return 0;
    }
    
    if( !player->moveAllowed( env->query_ghostExit( verb ) ) )
    {
        return 0;
    }
    
    if( player->has_to_wait( MOVE_WAIT_TIME_TYPE ) )
    {
        return 2;
    }

    if( player->GetPosition() != STAND )
    {
        tell_object( player, "You should stand up first.\n" );
        return 1;
    }

    tell_room( env->query_ghostExit( verb ), player->query_short() + env->query_ghostEnterString( verb ) + "\n", player );

    tell_room( env, player->query_short() + env->query_ghostExitString( verb ) + "\n", player );
            

    // Tell the player that the move happend
    tell_object( player, "You move to " + env->query_ghostExit( verb )->query_short() + ".\n\n" );

    player->move( env->query_ghostExit(verb) );

    player->set_wait_timer( MOVE_WAIT_TIME, MOVE_WAIT_TIME_TYPE );

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
int execute_movement(object player, string verb, string arg)
{
    object env;
    string tmp, custom;

    env = environment( player );

    if( !env ) 
    {
        return 0;
    }

    if( is_a( STREETS, env ) )
    {
        return execute_street_movement( player, verb, arg, env );
    }

    if( !env->valid_exit( verb ) )
    {
        if( wizardp( player ) || is_a( GHOST, player ) )
        {
            return execute_ghost_movement( player, verb, arg );
        }
        return 0;
    }

    if( !player->moveAllowed( env->query_exit( verb ) ) )
    {
        return 0;
    }
    
    if( player->has_to_wait( MOVE_WAIT_TIME_TYPE ) )
    {
        return 2;
    }

    if( player->GetPosition() != STAND )
    {
        tell_object( player, "You should stand up first.\n" );
        return 1;
    }

    if( !wizardp( this_user() ) && env->query_door_state( verb ) > 1 )
    {
        tell_room( env, player->query_cap_name() + " trys to go " + verb + " but the closed door has other ideas." + "\n", player );
        tell_object( player, "You bump into a closed door trying to go " + verb + ".\n" );
        return 1;
    }

    // Tell the room we are entering that we have
    if( player->query_env( "move_in" ) && wizardp( player ) )
    {
        custom = this_player()->query_env("move_in");
        tmp = custom;
        tmp = replace_string( tmp, "$N", player->query_cap_name() );
        tell_room( env->query_exit(verb), capitalize(tmp) + "\n", player );
    }
    else
    {
        tell_room( env->query_exit( verb ), player->query_cap_name() + " has entered the room.\n", player );
    }
            
    // Tell the room we are in that we are leaving
    if( player->query_env( "move_out" ) && wizardp( player ) )
    {
        custom = this_player()->query_env( "move_out" );            
        tmp = custom;
        tmp = replace_string(tmp, "$N", player->query_cap_name());
        tmp = replace_string(tmp, "$D", verb);
        tell_room( env, capitalize(tmp) + "\n", player );
    }
    else
    {
        tell_room( env, player->query_cap_name() + " leaves through the " + verb + " exit.\n", player );
    }

    // Tell the player that the move happend
    tell_object( player, "You move to " + environment(this_player())->query_exit(verb)->query_short() + ".\n\n" );

    player->move(environment(this_player())->query_exit(verb));

    player->set_wait_timer( MOVE_WAIT_TIME, MOVE_WAIT_TIME_TYPE );

    return 1;
}

/**
 * Checks the environment of the player for an exit that matches 'verb'
 *
 * @param player - player that issued this command
 * @param verb - command that was called
 * @param arg - additional arguments to the command
 * @param env - environment of the player
 *
 * @return int - 1 if this function handled the command
 */
int execute_street_movement(object player, string verb, string arg, object env)
{
    if( env )
    {
        return env->move_player( player, verb, arg );
    }
    return 0;
}

/**
 * Checks the players path for a matching command file then executes that command
 *
 * @param player - player that issued this command
 * @param verb - command that was called
 * @param arg - additional arguments to the command
 *
 * @return int - 1 if this function handled the command
 */
int execute_objectCommand( object player, string verb, string arg )
{
    string targetID;
    string commandArg;
    object target;

    if( !objectCommands )
    {
        return 0;
    }

    if( undefinedp( objectCommands[verb] ) )
    {
        return 0;
    }

    if( !arg || arg == "" )
    {
        return 0;
    }

    if( sscanf( arg, "%s %s", targetID, commandArg ) != 2 )
    {
        targetID = arg;
        commandArg = "";
    }

    target = present( targetID, this_user() );

    if( !target )
    {
        return 0;
    }

    foreach( string type in objectCommands[verb] )
    {
        if( is_a( type, target ) )
        {
            return call_other( target, verb, commandArg );
        }
    }

    return 0;
}

/**
 * Tells the player that they have a wait timer and need to wait
 *
 * @param palyer - the player to tell
 */
void issue_wait_time_err( object player )
{
    tell_object( this_user(), sprintf( "Whoa! slow down gotta wait %2.2f more seconds.\n", (float)player->query_time_left_to_wait() / 1000.0 ) );
}

/**
 * Returns the player that issued this command
 *
 * @return object - the current player
 */
object current_player()
{
    return currentPlayer;
}

/**
 * Sets the failed string called by the sim efun notify_falied
 *
 * @param[in] message - the message that should be displayed insted of "What?"
 */
void set_failed_string( string message )
{
    failString = message;
}
