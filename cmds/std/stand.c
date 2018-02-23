//
// /cmds/std/stand.c
//
inherit COMMAND;

/*
 One of the five position commands
 
 standing = 0
 sit = 1
 kneel =2
 lie = 3
 resting = 4;
 */
int query_wait_time( string arg );
int wasKD;

int main( string arg )
{
	
    
    object player=this_player();
    //        object furniture=player->GetFurniture();
    //                
    //        if(furniture)
    //        {
    //        
    //furniture->SetCurrentCapacity(furniture->GetCurrentCapacity()-//1);
    //       }
    
    /* If the player is knocked down, stand will bring him back to his feet for some
     Roundtime. -Critical */
    
    if(player->CheckForStatus("knockdown"))
    {
        player->ClearStatus("knockdown");
        write("Your hop back to your feet!\n");
        wasKD=1;
        say(player->query_cap_name() + " gets to his feet, recovering from being knocked down.\n");
        player->SetPosition(STAND);
        
        /*Add Round time of 3-5 seconds. Random()!*/
        return 1;
    }
    
    
    write("You stand up.\n");
    say(player->query_cap_name() + " stands up.\n");
    player->SetPositionPost("");            
    player->SetPosition(STAND);     
    return 1;
    
}

int query_wait_time( string arg ) 
{ 
    
    if(wasKD==1)
    {
        
        return random(2)+3*1000;
    }
    else
    {
        return 0;	
    }
    
    
    
} 
