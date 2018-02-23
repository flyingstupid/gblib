//restore.c
//Written by Criticalfault
// Heals a player to full health!
inherit COMMAND;

int main(string arg)
{

	object player=find_player(lower_case(arg));
	string name;
	
	if(!player)
	{
		write("That player isnt online!\n");
		return 1;
	}
	name=player->query_name();
	player->set_health(100);
	write(sprintf("%10s",capitalize(name) +" is fully healed.\n"));
	tell_object(player,"You have been fully restored!\n");
	return 1;
}
