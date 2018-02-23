/* close.c

 Emraef @ GBmud
 04-JUNE-09
 Standard command
*/

inherit COMMAND;
int main(string arg)
{
    string exit, thing;
    object env = environment( this_user() );

    if( arg == 0 || arg == "" )
    {
        tell_object( this_user(), "SYNTAX: close door <direction>\n" );
        return 1;
    }

    if( sscanf( arg, "%s %s", thing, exit ) != 2 || thing != "door" )
    {
        tell_object( this_user(), "SYNTAX: close door <direction>\n" );
        return 1;
    }

    if( !env->valid_exit( exit ) )
    {
        tell_object( this_user(), "There is no exit \"" + exit + "\".\n" );
        return 1;
    } 

    if( env->query_door_state( exit ) == 0 )
    {
        tell_object( this_user(), "There is no door for \"" + exit + "\" exit.\n" );
        return 1;
    }
    
    if( env->query_door_state( exit ) == 2 )
    {
        tell_object( this_user(), "That door is already closed.\n" );
        return 1;
    }

    tell_object( this_user(), "You close the door.\n" );
    tell_room( env, this_user()->query_cap_name() + " closes the door to the " + exit + ".\n", this_user() );
    env->set_door_state( exit, 2 );
    return 1;
}

string help()
{
     return(HIW + " SYNTAX: " + NOR + "close door <dir>\n\n"
     "This command will allow you to close a door.\n\n" );
}
