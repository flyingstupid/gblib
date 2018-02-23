inherit COMMAND;

void DoBarfAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
    
    DoBarfAttack( ob );
    
    return 1;
}



void DoBarfAttack( object Target )
{
	int roll;
	int diff=0;
	int gpower;
    
	gpower=this_object()->GetGhostPower();
	
	if(!gpower)
	{
		gpower=1;
	}
	
	
	diff=gpower*4;
	
	if(Target->CheckForStatus("slimed"))
	{
		diff=diff-10;
	}
	if(Target->CheckForStatus("knockdown"))
	{
		diff=diff-20;	
	}	
	
    //Init attack!
	roll=Target->DoSkillRoll("dodge",diff);
	
	if(roll > 1)
	{
		say(Target->query_cap_name() + " easily dodges the attack!\n");
	}
	else
	{
		say(Target->query_cap_name() + " doesn't react in time and is quickly covered in vomit!\n");
        Target->ApplyStatusEffects( "slimed");
        say(Target->query_cap_name() + " screams as the acidic vomit burns them!\n");
        Target->CauseDamage(gpower*2);
        
        //Slime player here!	^ is that it?!
        //Drop Research Sample here!
        
        
        //See if player can clear thier face. Diff is dodge failure!
        Target->DoSkillRoll("block",roll);
        if(roll > 1)
        {
            say(Target->query_cap_name() + " quickly throws up their hands to clear their face from the worst of it.\n");
        }	
        else
        {
            if(Target->CheckForStatus("knockdown"))
            {
                say(Target->query_cap_name() + " rolls around on the ground puking!\n");
            }
            else
            {
                say(Target->query_cap_name() + " can't clear their face fast enough are is quickly over come by the smell\n They hit the ground puking!\n");
                Target->ApplyStatusEffects( "knockdown");
            }
            
            // Setting the wait time its the same even if we were knocked down
            Target->set_wait_timer(5, 2 );
        }
        
        
    }
    
    
    
    
    
    
}
