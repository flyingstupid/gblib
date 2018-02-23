//GetSkills.c
//Written by Criticalfault

inherit COMMAND;

int main(string arg)
{


object player=find_player(lower_case(arg));
string *keysArray; 
string name;
   

if(!player)
{
	write("They are logged in!\n");
	return 1;
}

	keysArray = keys(player->get_skills());
	name = player->query_name();


    write("|======[Skills - "+ sprintf("%10s",capitalize(name)) +
"]=======|\n");
    
    for(int i=0; sizeof(keysArray)>i; i++)
    {    
        printf( "| %-19s:%-12d |\n",
keysArray[i],player->get_skill(keysArray[i])  );
    }


    write("|==================================|\n");



    return 1;
}

