//
// /cmds/npc/ghosttrip.c
//





inherit COMMAND;

void DoTripAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
    
    DoTripAttack( ob );
    
    return 1;
}



void DoTripAttack( object Target ){
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
                diff=diff+10;
        tell_object(Target, "You are slimed making it harder to dodge!\n");
        
        }
        if(Target->CheckForStatus("knockdown"))
        {
                diff=diff+20;   
        tell_object(Target, "You are knocked down making it harder to
dodge!\n");
        }
    
    //Init attack!
        roll=Target->DoSkillRoll("dodge",diff);
    
    
    tell_object(Target,this_player()->query_cap_name() + " tries to trip
you!\n");
    write("You try to trip " + Target->query_cap_name() + "\n");
    tell_room(environment(this_player()), this_player()->query_cap_name() + "
attempts to trip "+ Target->query_cap_name()+"!\n", ({ Target }) );
    
        
        if(roll > 1)
        {
                say(Target->query_cap_name() + " easily dodges the attack!\n");
        }
    else
        {
                tell_room(environment(this_player()), Target->query_cap_name()
+ " doesn't react in time and knocked to the ground!\n", ({ Target }) );
        write("You knock " + Target->query_cap_name() + " to the gound!\n");
        tell_object(Target, this_player()->query_cap_name() + " trips you!\n");
                  
                  
                  
        Target->ApplyStatusEffects( "knockdown");
        tell_room(environment(this_player()), Target->query_cap_name() + " falls
to the ground in a pathetic heap.\n", ({ Target }) ); 
        
                  
        Target->CauseDamage(gpower*2);
        
        //Slime player here!    ^ is that it?!
        //Drop Research Sample here!
        
        
        //See if player can jump back to their feet. Diff is dodge failure!
        Target->DoSkillRoll("block",roll);
        if(roll > 1)
        {
            say("In an act of skilled acrobatics, " + Target->query_cap_name() +
" leaps back to their feet and grins rakishly at " +
this_player()->query_cap_name() + ".\n");
            Target->ClearStatus( "knockdown");
        }       
        else
        {
            say(Target->query_cap_name() + " tries to regain their balance but
only ends up landing on their ass.\n");
            //Target->ApplyStatusEffect( "knockdown");
            //Add 5 sec RT...but how?!
        }        
    }
}
