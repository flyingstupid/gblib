inherit COMMAND;
/* Janine's FirstAid command! */




/* functions */
int targetInRoom(string target);
void DoPatch(object victim);
void heal(object victim, int skillRole);
int calcHeal();
int query_wait_time( string arg );



int main (string arg)
{
        string target;
        string action;
        object victim;
    int targetHealth;

    
    if (!arg){
        tell_object( this_player() , "firstaid <action> <target>  ex. firstaid patch emraef \n");
        return 1;
    }
    
    
    query_wait_time(arg);
    
    sscanf(arg,"%s %s", action, target);

    target = lower_case(target);
    victim = find_player(target);
     
    
    if (targetInRoom(target)){
       
        targetHealth = victim->get_health();
      
    }
    else
    {
        tell_object( this_player() , "That person is not here!\n");
        return 1;
    }
    if (victim->get_health() < 100)
    {

        if (action == "patch")
        {
            DoPatch(victim);
            return 1;
        }
    }
    else
    {        

        tell_object( this_player() ,"After examining  " +victim->query_cap_name() + ", you discover they are in perfect condition!\n");
        return 1;
    }
    
}


int query_wait_time( string arg )
{
	    string target;
        string action;
        object victim;
	
        if(!arg)
        {
	        return 1;
        }
        
	sscanf(arg,"%s %s", action, target);

		if(!target)
	{
		return 1;	
	}

	
	if(!target)
	{
		return 1;	
	}
	
	if(action=="patch")
	{
		return 4000;
	}
	
}

int targetInRoom(string target)
{
    object *room;
    
    room = all_inventory( environment( this_player() ));
    for( int i = 0; i < sizeof( room ); i++ )
    {
        if( is_a (PLAYER, room[ i ] ))
        {
            if ( room[ i ]->query_name() == target)
            {
                return 1;
            }
            
        }
    }
    return 0;
}

void DoPatch(object victim)
{
    int skillRole;
    int diff;
    
    
    diff = 100-victim->get_health();
    skillRole = this_player()->DoSkillRoll("firstaid",diff);
    if (skillRole > 0)
    {
	    tell_room( environment( this_player() ), this_player()->query_cap_name() + " patches up " + victim->query_cap_name() + ".\n");
        heal(victim, skillRole);
    }
    else
    {
        tell_object( this_player() , "You fail to patch up " +
victim->query_cap_name() + ".\n");
        tell_room( environment( this_player() ), this_player()->query_cap_name()
+ " fails to patch up " + victim->query_cap_name() + "\n");
       
    }
}

void heal(object victim, int skillRole)
{
    int healAmount;
    int newHealth;
    
   
    healAmount = (skillRole/3);
    //healAmount = calcHeal();
    newHealth = victim->get_health()+healAmount;
   
    victim->set_health(newHealth); 
}

int calcHeal(){
    int healAmount;
    int base;
    
    base = random(10) + 1;
    
    
    for( int i = base; i > 0; i-- )
    {
        healAmount = healAmount + (random(10)+1);
    }
    return healAmount;
    
}

