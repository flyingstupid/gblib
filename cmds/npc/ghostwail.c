inherit COMMAND;

void DoWailAttack( object Target );

int main( string arg )
{
    object ob;

    ob = present(arg, environment( this_user() ) );

    if( !ob ) {
        tell_object( this_user(1), "Error target: [" + arg + "] Not Found.\n" );
        return 1;
    }

    DoWailAttack( ob );

    return 1;
}



void DoWailAttack( object Target )
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
        
        if(Target->CheckForStatus("slimed"));
        {
                diff=diff+10;
        }
      
        
                
        
        write("You wail at "+ Target->query_cap_name()+"\n");
        tell_room(environment(this_player()), this_player()->query_cap_name() +" wails at " + Target->query_cap_name()+"\n", ({ Target }) );
        tell_object(Target, this_player()->query_cap_name() + " begins to wail at you!\n"); 
        roll=Target->DoSkillRoll("block",diff);
        
        if(roll > 1)
        {
            write("Your wailing seems to not affect "+ Target->query_cap_name()+"\n");
            tell_room(environment(this_player()), Target->query_cap_name() + " throws their hands over their ears quickly!\n", ({ Target }) );
            tell_object(Target, "You throw your hands over your ears and the sinking feeling fades quickly.\n");
        }
        else
        {    
            write("Your wail shakens " +Target->query_cap_name() +"!\n");
            tell_room( environment(this_player()), this_player()->query_cap_name() +" shakens " + Target->query_cap_name() +"!\n", ({ Target }) ); 
            tell_object(Target," You fail to cover your ears quick enough and the wail terrorifies you!\n");
            Target->ApplyStatusEffects("shaken");      
        }
       
}
