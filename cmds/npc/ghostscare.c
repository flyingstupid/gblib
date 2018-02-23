inherit COMMAND;

void DoScareAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }    
    DoScareAttack( ob );
    return 1;
}

void DoScareAttack( object Target )
{
	int roll=random(100)+1;
    string *exits;
    object room=environment(this_player());
     
	    write("You scream at " + Target->query_cap_name() + "\n");
    	tell_object(Target,this_player()->query_cap_name() + " screams and tries to scare you!\n");
    	tell_room(environment(this_player()), this_player()->query_cap_name() + " screams at "+ Target->query_cap_name()+"!\n", ({ Target }) );
 
	if(roll>50)
	{
		write("You scare the bejesus out of " + Target->query_cap_name() + "\n");
    	tell_object(Target,this_player()->query_cap_name() + " scares the bejesus out of you!\n");
    	tell_room(environment(this_player()), this_player()->query_cap_name() + " scares "+ Target->query_cap_name()+"!\n", ({ Target }) );
 		exits = keys(room->query_exits());
 		Target->command(exits[random(sizeof(exits))]);	
	}
	else
	{
		write("You fail to scare " + Target->query_cap_name() + "\n");
    	tell_object(Target,this_player()->query_cap_name() + " tries to scare you, but you shake it off!\n");
    	tell_room(environment(this_player()), this_player()->query_cap_name() + " fails to scare "+ Target->query_cap_name()+"!\n", ({ Target }) );	
	}
	
}
