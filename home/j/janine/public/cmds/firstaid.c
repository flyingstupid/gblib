inherit COMMAND;
/* need to know how to increase victim's health and how to make target lowercase
 also how to clear white space from target*/




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
        tell_object( this_player() , "firstaid <action> <target>  ex. firstaid patch emrafe \n");
        return 1;
    }
    
    
    query_wait_time(arg);
    
    sscanf(arg,"%s %s", action, target);

    target = lower_case(target);
    victim = find_player(target);
     
    
    if (targetInRoom(target)){
        tell_room( environment( this_player() ), "The target is here\n" );
        tell_object( this_player(), "The target is here\n" );
        targetHealth = victim->get_health();
        tell_room( environment( this_player() ), "target's health is " + targetHealth +"\n");
        tell_object( this_player(), "target's health is " + targetHealth +"\n");
    }else{
        tell_room( environment( this_player() ), "the target is not here\n");
        tell_object( this_player() , "the target is not here\n");
        return 1;
    }
    if (victim->get_health() < 100){
        tell_room( environment( this_player() ), "target needs to be healed.\n");
        tell_object( this_player() , "target needs to be healed.\n");
        if (action == "patch"){
            DoPatch(victim);
            return 1;
        }
    }else{        
        tell_room( environment( this_player() ),victim->query_cap_name() + "is already in perfect condition!\n");
        tell_object( this_player() ,victim->query_cap_name() + "is already in perfect condition!\n");
        return 1;
    }
    
}


int query_wait_time( string arg ){
    return 3000;
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
    tell_room( environment( this_player() ), "the difficulty is " + diff + "\n");
    tell_object( this_player() , "the difficulty is " + diff + "\n");
    skillRole = this_player()->DoSkillRoll("firstaid",diff);
    tell_room( environment( this_player() ), "the skill rolls is " + skillRole + "\n");
    tell_object( this_player() , "the skill rolls is " + skillRole + "\n");
    if (skillRole > 0){
        heal(victim, skillRole);
    }
    else{
        tell_object( this_player() , "You fail to heal " + victim->query_cap_name() + ".\n");
        tell_room( environment( this_player() ), this_player()->query_cap_name() + " fails to heal " + victim->query_cap_name() + "\n");
        tell_room( environment( this_player() ), "healing failed\n");
    }
}

void heal(object victim, int skillRole){
    int healAmount;
    int newHealth;
    
    tell_room( environment( this_player() ), "in heal.\n");
    tell_object( this_player(), "in heal.\n");
    
    healAmount = (skillRole/3);
    //healAmount = calcHeal();
    newHealth = victim->get_health()+healAmount;
    tell_room( environment( this_player() ), "victim health is " + victim->get_health() + "\n");
    tell_object( this_player() , "victim health is " + victim->get_health() + "\n");
    victim->set_health(newHealth);
    tell_room( environment( this_player() ), "victim health is " + victim->get_health() + "\n");
    tell_object( this_player() , "victim health is " + victim->get_health() + "\n");    
}

int calcHeal(){
    int healAmount;
    int base;
    
    base = random(10) + 1;
    tell_object( this_player() , "base: " + base + "\n");
    
    for( int i = base; i > 0; i-- )
    {
        healAmount = healAmount + (random(10)+1);
    }
    tell_object( this_player() , "Heal Amount: " + healAmount + "\n");
    return healAmount;
    
}




