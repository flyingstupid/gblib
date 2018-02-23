inherit COMMAND;

/*
   One of the five position commands

   standing = 0
   sit = 1
   kneel =2
   lie = 3
   resting = 4
 */


int main( string arg )
{
    object player=this_player();
    object furniture;

    if(!arg)
    {
        write("You sit down.\n");
        say(player->query_cap_name() + " sits down.\n");
        player->SetPosition(SIT);	
        return 1;
    }

    furniture=present(arg,environment(this_player()));
    if(!furniture)
    {
        write("You can't find a " + arg + " to sit on!\n");
        return 1;	
    }
    else
    {

        if(furniture->CanSit()&& !furniture->IsFull())
        {
            player->SetFurniture(furniture);
            furniture->SetCurrentCapacity( furniture->GetCurrentCapacity()+1);
            write("You sit on "+ furniture->query_short()+".\n");
            say(this_player()->query_short() +" sits on "+ furniture->query_short());
            player->SetPosition(SIT);
            player->SetPositionPost(" is sitting on " + furniture->query_short());
            return 1;
        }
        else if(furniture->IsFull())
        {
            write("That is too full to sit on!\n");
            return 1;

        }
        else
        {
            write("You either can't sit on " + arg+" or it is full\n");
            return 1;
        }
    }	




}
