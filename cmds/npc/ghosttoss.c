inherit COMMAND;

void DoTossAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
    
    DoTossAttack( ob );
    
    return 1;
}

void DoTossAttack ( object Target )
{
	int roll;
    int diff=0;
    int gpower;
    int damholder;
    int totaldam=0;
	string tossobject;
	object room;
	
	
	gpower=this_object()->GetGhostPower();
    
    if(!gpower)
    {       
        gpower=5;
    }
    
    
    diff=gpower*3;
    
    if(Target->CheckForStatus("slimed"))
    {
        diff=diff+10;
    }
    if(Target->CheckForStatus("knockdown"))
    {
        diff=diff+10;   
    }
    if(Target->CheckForStatus("broken_arm"))
    {
	   diff=diff+30;   
    }
    room = environment( this_player() );
    tossobject = room->get_onetoss();
    roll = Target->DoSkillRoll("block",diff);
    
    if(!tossobject)
    {
    	tossobject="thing";
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
        to_int(damholder=(roll*(-1)/10));
        if(damholder<1)
        {
            damholder=1;
        }
        if(damholder>5)
        {
            damholder=5;    
        }
        write("The "+ tossobject +" strikes true.\n");
        tell_object(Target, "You are struck!\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is struck!\n", ({Target }) );
     
        totaldam=gpower*damholder;
        Target->CauseDamage(totaldam);
    }
		
}
