inherit COMMAND;

void DoHurlAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
    
    
    call_out("DoHurlAttack",5,ob);
    
    return 1;
}

void DoHurlAttack ( object Target )
{
	int roll;
    int diff=0;
    int gpower;
    int totaldam=0;
    string tossobject;
	object hurlableobject;
	object room;
	
	
	gpower=this_object()->GetGhostPower();
    
    if(!gpower)
    {       
        gpower=5;
    }
        
    diff=gpower*5;
    
    if(Target->CheckForStatus("slimed"))
    {
        diff=diff+10;
    }
    if(Target->CheckForStatus("knockdown"))
    {
        diff=diff+20;   
    }
    if(Target->CheckForStatus("broken_leg"))
    {
	   diff=diff+30;   
    }
    if(Target->CheckForStatus("splinted_leg"))
    {
	 	diff=diff+20;   
    }
    room = environment( this_player() );
    tossobject=hurlableobject->query_short();
    hurlableobject = room->find_hurlable();
    roll = Target->DoSkillRoll("dodge",diff);
    
    if(!hurlableobject)
    {
    	write("You can't find something to vent your anger on!\n");
	    return;
	}
	
    write("You hurl a "+ tossobject +" at " + Target->query_cap_name() + "\n");
    tell_object(Target,"Suddenly a "+ tossobject +" flies at you!\n");
    tell_room(environment(this_player()), "Suddenly a "+ tossobject +" flies at "+Target->query_cap_name()+"\n", ({ Target }) );
    
    
    if(roll > 1)
    {
        write("They dodge it easily.\n");
        tell_room(environment(this_player()), " \n"+Target->query_cap_name() + "easily dodges the attack!\n", ({ Target }) );
        tell_object(Target, "You easily dodge the attack!\n");
    }
    else
    {

        write("The "+ tossobject +" strikes true.\n");
        tell_object(Target, "You are struck!\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is struck!\n", ({Target }) );     
        totaldam=gpower*5;
        Target->CauseDamage(totaldam);
        hurlableobject->Tossed();        
    }
	
}
