inherit COMMAND;

void DoScreamAttack( object Target );

int main( string arg )
{
    object ob;
    
    ob = present(arg, environment( this_user() ) );
    
    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }    
    DoScreamAttack( ob );
    return 1;
}




void DoScreamAttack( object Target )
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
    
    roll=Target->DoSkillRoll("block",diff);
    
    write("You scream at " + Target->query_cap_name() + "\n");
    tell_object(Target,this_player()->query_cap_name() + " screams at you!\n");
    tell_room(environment(this_player()), this_player()->query_cap_name() + " screams at "+ Target->query_cap_name()+"!\n", ({ Target }) );
    
    if(roll > 1)
    {
        write("They throw their hands over their ears.\n");
        tell_room(environment(this_player()), " \n"+Target->query_cap_name() + " protects their ears from the assault!\n", ({ Target }) );
        tell_object(Target, "You throw your hands over your ears and are protected!\n");
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
        write("Your scream shatters them.\n");
        tell_object(Target, "You ears ring and you frame is shattered by the scream!\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is staggered by the scream!\n", ({Target }) );
        totaldam=(gpower*2)*damholder;
        Target->CauseDamage(totaldam);
    }
    
    
    if(totaldam>=30 && !Target->CheckForStatus("knockdown"))
    {
        tell_object(Target, "You're knocked off your feet!\n");
        write("You knock them off their feet.\n");
        tell_room(environment(this_player()), Target->query_cap_name() + " is knocked off their feet from the attack!\n", ({ Target }) );
        Target->ApplyStatusEffects( "knockdown");      
    }   
}
