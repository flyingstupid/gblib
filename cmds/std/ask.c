//
//
//    /cmds/std/ask.c    
//    By Critical
//    
//    
inherit COMMAND;
void ask(object person, string word);



int main(string arg)
{
    object ob;
    string target;
    object *room;
    string keyword;
    string reply;
    
    
    if(!arg)
    {
        write("SYNTAX: Ask <Mobile> <Keyword>\n");
        return 1;
    } 
    
    sscanf(arg,"%s %s", target, keyword);
    
    //room=all_inventory(environment(this_player()));
    
    
    ob = present( target, environment( this_player() ) );
    
    /*
     for(int i=0; i<sizeof(room);i++)
     {
     if(room[i]->askOk())
     {
     target=room[i];
     }
     
     }
     */
    if (ob){
        write ("the " +ob->query_short() + " replies: \n");
        write (ob->query_reply(keyword) + "\n");
    }
    else {
        write("That person isn't here\n");
    }
    return 1;
}


/*
void ask(object person, string word)
{
    mapping responses;
    string respkey;
    
    responses = person->
    respkey = keys(responses);
    
    foreach (respkey in responses )
    {
        if(m[i]==word)
        {
            say(person->query_cap_name() + " sayes: " + m[k[i]] + "\n");
            // Force mob to say reply   
            break;  
        }
        
        
    }
    
}

*/
