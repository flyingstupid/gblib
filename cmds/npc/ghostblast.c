inherit COMMAND;

void DoBlastAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }
    
    DoBlastAttack( ob );
    
    return 1;
}




void DoBlastAttack( object Target )
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
    
    
    diff=gpower*3;
    
    if(Target->CheckForStatus("slimed"))
    {
        diff=diff+10;
    }
    if(Target->CheckForStatus("knockdown"))
    {
        diff=diff+20;   
    }
    
    roll=Target->DoSkillRoll("dodge",diff);
    
    write("You hurl a blast at " + Target->query_cap_name() + "\n");
    tell_object(Target,this_player()->query_cap_name() + " hurls a blast at you!\n");
    tell_room(environment(this_player()), this_player()->query_cap_name() + " hurls a bolt of energy at "+ Target->query_cap_name()+"!\n", ({ Target }) );
    
    
    //say(this_player()->query_cap_name() + " hurls a bolt of energy at "+ Target->query_cap_name()+"!\n");
    
    if(roll > 1)
    {
        write("They dodge it easily.\n");
        tell_room(environment(this_player()), " \n"+Target->query_cap_name() + " easily dodges the attack!\n", ({ Target }) );
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
        write("The blast strikes true.\n");
        tell_object(Target, "You are struck!\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is struck!\n", ({
            Target }) );
        //say(Target->query_cap_name() + " is struck!\n");
        totaldam=(gpower*2)*damholder;
        //say("[]    " + totaldam + "     []\n");
        Target->CauseDamage(totaldam);
    }
    
    
    if(totaldam>=30 && !Target->CheckForStatus("knockdown"))
    {
        tell_object(Target, "You're knocked off your feet!\n");
        write("You knock them off their feet.\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is knocked off their feet from the attack!\n", ({ Target }) );
        //say(Target->query_cap_name() + " is knocked off their feet from the attack!\n");
        Target->ApplyStatusEffects( "knockdown");    
        
    }
    
    
}
