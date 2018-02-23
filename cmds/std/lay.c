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
		write("You lay down.\n");
		say(player->query_cap_name() + " lays down.\n");
		player->SetPosition(LAY);
		return 1;	
	}
	
	
	furniture=present(arg,environment(this_player()));
	if(!furniture)
	{
		write("You can't find a " + arg + " to lay on!\n");
		return 1;	
	}
	else
	{
		if(furniture->CanLay() && !furniture->IsFull())
		{
			player->SetFurniture(furniture);
			furniture->SetCurrentCapacity( furniture->GetCurrentCapacity()+1);
			write("You lay on "+ furniture->query_short() + "\n");
			say(this_player()->query_short() +" lays on "+ furniture->quert_short());
			player->SetPosition(LAY);
			player->SetPositionPost(" is sitting on " + furniture->query_short());
		}
		else if(furniture->IsFull())
		{
			write("That is too full to lay on!\n");
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