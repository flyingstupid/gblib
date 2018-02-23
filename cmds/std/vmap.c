/* vmap.c

 Emraef @ GB123
 06-FEB-07
 Standard command
 
*/
inherit COMMAND;
int main(string arg)
{
    object room;

    room = environment( this_user() );

    if( room )
    {
        tell_object( this_user(), room->vmap() + "\n" );
    }

    return 1;
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "vmap\n\n" +
      "This will display the virtual map for the the room you are in\n");
}
