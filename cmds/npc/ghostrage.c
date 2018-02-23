inherit COMMAND;


int main( string arg )
{
	int power;
	int newpower;
	if(!this_player()->IsGhost())
	{
		write("Your not a ghost!\n");
		return 1;	
	}
	power=this_player()->GetGhostPower();
	newpower=power+(power/5);
        if(newpower < 1 )
        {
             newpower=1;
        }
	if(this_player()->GetRage()==1)
	{
		write("Your extremely pissed already.\n");		
	}
	else
	{
		write("You think about everything horrible thing that happend to you in life and burn with rage!\n");	
		tell_room(environment(this_player()),this_player()->query_cap_name() + " screams in RAGE!\nIt seems more powerful now.\n", ({ this_player() }) );
		this_player()->SetGhostPower(newpower);
		this_player()->SetRage(1);			
	}

	return 1;
}
