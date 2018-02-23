/**
 * command.c
 *
 * Emraef @ GhostBustersMUD
 * 27-MAY-09
 * Base command interface
 */

int query_wait_type( string arg )
{
    return 5;
}

int query_wait_time( string arg )
{
    return 0;
}

int issue_wait_timer( object player, string arg )
{
    if( !player )
    {
        return 0;
    }

    if( !is_a( MOBILE, player ) )
    {
        return 0;
    }

    player->set_wait_timer( query_wait_time( arg ), query_wait_type( arg ) );

    return 1;
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "NEW COMMAND!\n\n" + 
        "YOU NEED TO ADD THE HELP TEXT TO THE COMMAND n00b!\n" );
}

void say_room( string message )
{
    tell_room( environment( this_user() ), message, this_user() );
}
