inherit COMMAND;

int main(string arg)
{
	object player;
	string playername;
	string skill;
	int value;
	
	
	sscanf(arg,"%s %s %d",playername,skill,value);	
	
	player=find_player(lower_case(playername));
	
	if(!player)
	{
		
		write("They aren't online!\n");
	
	}
	else
	{
		if(value<500)
		{
		player->set_skill(skill,value);
		write("%^BOLD%^WHITE%^[%^RED%^Wizard%^WHITE%^]%^RESET%^ Set "+capitalize(player->query_name()) + "'s " +skill+": " + value +"\n");
		}
		else
		{
			write("You can not set a skill above 500.\n");
		}
	}
	return 1;
	
	
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "skillset [name] [skillname][skillvalue]\n"
      "Skillset sets a new skill or skill already on a player to the level you give.\n");
}