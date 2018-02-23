inherit COMMAND;

/*
One of the five position commands

standing = 0
sit = 1
kneel =2
lie = 3
resting = 4;
*/


int main( string arg )
{
	object player=this_player();
	object furniture;
	
	if(!arg)
	{
		write("You resting.\n");
		say(player->query_cap_name() + " moves to a resting position.\n");
		player->SetPosition(REST);	
		return 1;
	}
	
	
	furniture=present(arg,environment(this_player()));
	if(!furniture)
	{
		write("You can't find a " + arg + " to rest on!\n");
		return 1;	
	}
	else
	{
		if(furniture->CanRest() && !furniture->IsFull())
		{
			player->SetFurniture(furniture);
			furniture->SetCurrentCapacity( furniture->GetCurrentCapacity()+1);
			write("You rest on "+ furniture->query_short() + "\n");
			say(this_player()->query_short() +" rests on "+ furniture->quert_short());
			player->SetPosition(REST);
			player->SetPositionPost(" is resting on " + furniture->query_short());
			return 1;
		}
		else if(furniture->IsFull())
		{
			write("That is too full to rest on!\n");
			return 1;
		}
		else
		{
			write("You can't lay on" + arg + "\n");
			return 1;
		}
	}		
	
	
	
	
	
	
	return 1;
	
		
}