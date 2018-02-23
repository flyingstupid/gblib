inherit COMMAND;

void DoAreaBlastAttack( object primetarget );
void DoBoom(objects *targets );

object *targets;


int main( string arg )
{
    object primetarget;
    
    ob = present(arg, environment( this_user() ) );
    
    targets=all_inventory(environment(ob));
    
    
    if( !primetarget ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
        write("You begin to build up your PKE and stare at " + Target->query_cap_name() + " with hate.\n");
    tell_object(Target,this_player()->query_cap_name() + " begins to glow with power as it stares directly at you...\n");
    tell_room(environment(this_player()), this_player()->query_cap_name() + " begins to glow with power as it stares death at "+ Target->query_cap_name()+"!\n", ({ Target }) );
    call_out("DoAreaBlastAttack",5,primetarget);
    
    return 1;
}




void DoAreaBlastAttack( object primetarget )
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
    
    
    diff=gpower*6;
    
    if(Target->CheckForStatus("slimed"))
    {
        diff=diff+10;
    }
    if(Target->CheckForStatus("knockdown"))
    {
        diff=diff+20;   
    }
    
    roll=Target->DoSkillRoll("roll",diff);
    
    write("You finally let go of the hate you've built at " + Target->query_cap_name() + "\n");
    tell_object(Target,this_player()->query_cap_name() + " hurls a ball of pure hatred at you!\n");
    tell_room(environment(this_player()), this_player()->query_cap_name() + " hurls a ball of pure hate at "+ Target->query_cap_name()+"!\n", ({ Target }) );
    

    
    if(roll > 1)
    {
        write("They roll out of the blasts way!\n");
        tell_room(environment(this_player()), " \n"+Target->query_cap_name() + " rolls under the ball of power!\n", ({ Target }) );
        tell_object(Target, "You roll away from the ball of power!\n");
    }
    else
    {
        to_int(damholder=(roll*(-1)/5));
        if(damholder<1)
        {
            damholder=1;
        }

        write("The ball strikes true and your vengence seethes within you\n");
        tell_object(Target, "You are struck by the ball and your soul shudders as it passes through you!\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is struck!\nSuddenly the ball EXPLODES", ({ Target }) );
        totaldam=(gpower*2)+damholder;
        Target->CauseDamage(totaldam);
    }
    
    
    if(totaldam>=30 && !Target->CheckForStatus("knockdown"))
    {
        tell_object(Target, "You're knocked off your feet!\n");
        write("You knock them off their feet.\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is
knocked off their feet from the attack!\n", ({ Target }) );
        //say(Target->query_cap_name() + " is knocked off their feet from the
attack!\n");
        Target->ApplyStatusEffects( "knockdown");    
        
    }
    
    
}

void DoBoom( *targets )
{

return;
}
