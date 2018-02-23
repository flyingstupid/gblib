inherit COMMAND;


int main( string target )
{
        object player;
        

	if(!target)
	{
	write("You need to specify a target!");
	return 1;
	}


    target=lower_case(target);
        player=find_player(target);



	        
        if(!objectp(player)) return notify_fail("Error [statusclear]: " +
target + " not found.\n");
        if(!living(player)) return notify_fail("Error [statusclear]: That
object is not living.\n");
        player->ClearAllStatuses();
        write("You clear " + capitalize(target) + " of their statuses\n");
        return 1;




}
