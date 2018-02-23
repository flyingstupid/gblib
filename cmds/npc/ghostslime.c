inherit COMMAND;

void DoSlimeAttack( object Target );

int main( string arg )
{
    object ob;

    ob = present(arg, environment( this_user() ) );

    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }

    DoSlimeAttack( ob );

    return 1;
}



void DoSlimeAttack( object Target )
{
        int roll;
        int diff=0;
        int gpower;

        gpower=this_object()->GetGhostPower();
        
        if(!gpower)
        {
                gpower=1;
        }
        
        
        diff=gpower*5;
        
        if(Target->CheckForStatus("slimed"));
        {
                diff=diff+10;
        }
        if(Target->CheckForStatus("knockdown"));
        {
                diff=diff+20;   
        }       
        
                
        
        write("You attempt to slime "+ Target->query_cap_name()+"\n");
        tell_room(environment(this_player()), this_player()->query_cap_name() +" tries to slime " + Target->query_cap_name()+"\n", ({ Target }) );
        tell_object(Target, this_player()->query_cap_name() + " tries to slime you!\n"); 
        roll=Target->DoSkillRoll("dodge",diff);
        
        if(roll > 1)
        {
            write("You fail to slime "+ Target->query_cap_name()+"\n");
            tell_room(environment(this_player()), Target->query_cap_name() + " easily dodges the attack!\n", ({ Target }) );
            tell_object(Target, "You easily dodge the attack!\n");
        }
        else
        {
                
            write("You slime " +Target->query_cap_name() +"!\n");
            tell_room( environment(this_player()), this_player()->query_cap_name() +" slimes " + Target->query_cap_name() +"!\n", ({ Target }) ); 
            tell_object(Target," You fail to move quick enough and are covered in slime!\n");
            Target->ApplyStatusEffects( "slimed");
               
        }
        
        
        if(roll<=-50)
        {
            write("You slime " +Target->query_cap_name()+" so hard they hit the ground!\n");
            tell_object(Target, this_player()->query_cap_name() +" slimes you so hard your knocked off your feet!\n");
            tell_room( environment(this_player()), Target->query_cap_name() + " tries to recover too quickly and slips in the slime now on the ground!\n", ({ Target }) );
            Target->ApplyStatusEffects( "knockdown");
            Target->CauseStatus_knockdown();

        }
        
        
}
