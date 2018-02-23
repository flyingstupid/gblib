inherit COMMAND;

void DoShriekAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
    write("You take in a deep ethereal breath to shatter " + ob->query_cap_name() + "\n");
    tell_object(ob,"An ethereal wind begins to blow around " + ob->query_cap_name() + "\n");
    tell_room(environment(this_player()),"An ethereal wind begins to blow around  "+ ob->query_cap_name()+"!\n", ({ ob }) );
    
    call_out("DoShriekAttack",4, ob);
    
    return 1;
}




void DoShriekAttack( object Target )
{
    int roll;
    int diff=0;
    int gpower;
    int totaldam=0;
    float damholder;
    
    
    gpower=this_object()->GetGhostPower();
    
    if(!gpower)
    {       
        gpower=5;
    }
    
    
    diff=gpower*4;
    
    if(Target->CheckForStatus("slimed"))
    {
        diff=diff+10;
    }
    if(Target->CheckForStatus("splinted_arm"));
    {
	    diff=diff+20;
    }
    if(Target->CheckForStatus("broken_arm"));
    {
	    diff=diff+30;
    }
    
    roll=Target->DoSkillRoll("block",diff);
    
    write("You release your shriek at " + Target->query_cap_name() + "\n");
    tell_object(Target,this_player()->query_cap_name() + " releases an ear piercing shriek at you!\n");
    tell_room(environment(this_player()), this_player()->query_cap_name() + " releases a ear piercing shriek at "+ Target->query_cap_name()+"!\n", ({ Target }) );

    
    if(roll > 1)
    {
        write("They seem unaffected.\n");
        tell_room(environment(this_player()), " \n"+Target->query_cap_name() + " throws their hands up and staggers backwords, but seems fine!\n", ({ Target }) );
        tell_object(Target, "You throw your hands up and seem to be able to withstand the shriek!\n");
    }
    else
    {
        to_int(damholder=(roll*(-1)/15));
        if(damholder<1)
        {
            damholder=1;
        }
        if(damholder>5)
        {
            damholder=5;    
        }
        if(!Target->CheckForStatus("broken_arm") && roll <= -25)
        {
       		 write("Your shriek strikes them. Their arm shatters!\n");
      		 tell_object(Target, "You throw your arms up and can't seem to shrug off the blow...Your arm shatters from the impact! ");
       		 tell_room(environment(this_player()), Target->query_cap_name() + "'s throws their arms up and it shatters as the shriek echos through their core. \n", ({ Target }) );
      	  	 Target->CauseDamage(totaldam);
      	  	 Target->ApplyStatusEffects("broken_arm");
    	}
    	else
    	{
	         write("Your shriek strikes them. Their arm is already shattered however!\n");
      		 tell_object(Target, "You throw your arms up and can't seem to shrug off the blow with your broken arm! ");
       		 tell_room(environment(this_player()), Target->query_cap_name() + " throws up their arms but is to hurt to push off the attack!\n", ({ Target }) );
      	  	 Target->CauseDamage(totaldam);		
    	}

    }
            
}
