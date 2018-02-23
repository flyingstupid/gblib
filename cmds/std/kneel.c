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
		write("You kneel down.\n");
		say(player->query_cap_name() + " kneels down.\n");
		player->SetPosition(KNEEL);	
		return 1;
	}
	furniture=present(arg,environment(this_player()));
	if(!furniture)
	{
		write("You can't find a " + arg + " to kneel on!\n");
		return 1;	
	}
	else
	{
			
			if(furniture->CanKneel() && !furniture->IsFull())
			{
				player->SetFurniture(furniture);
				furniture->SetCurrentCapacity( furniture->GetCurrentCapacity()+1);
				write("You kneel on "+ furniture->query_short()+"\n");
				say(this_player()->query_short() +" kneels on "+ furniture->quert_short());
				player->SetPosition(KNEEL);
				player->SetPositionPost(" is kneeling on " + furniture->query_short());
				return 1;
			}
			else if(furniture->IsFull())
			{
				write("That is too full to kneel on!\n");
				return 1;
			}
			else
			{
				write("You can't kneel on " + arg+"\n");
				return 1;
			}
	}	
	
		
	return 1;
	
		
}