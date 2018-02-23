// Damage!
//Written by Criticalfault

inherit COMMAND;

int main(string arg)
{

	string pstring;
	object player;
	int damage;		

	
if(!arg)
{
	write("SYNTAX:damage <player> <amount>");
	return 1;
}
		
sscanf(arg,"%s %d",pstring, damage);

player=find_player(lower_case(pstring));


if(!player)
{
        write("They are logged in!\n");
        return 1;
}
if(!damage)
{
	write("You need to do SOME damage!\n");
	return 1;
}

player->CauseDamage(damage);
write("You damage " + player->query_cap_name() + " for " + damage +"\n");




    return 1;
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "damage [name] [amount]\n"
      "Damage applies the amount of hit point loss specified in the amount to any player in the game.\n");
      
}
