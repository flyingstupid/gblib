/* remove.c

 emraef @ gbmud
 28-FEBRUARY-12
 Standard Command

*/
inherit COMMAND;
int main(string arg)
{
    object ob;
    string obName;

    if(!arg)
    {
        return(notify_fail("SYNTAX: remove <item>\n"));
    }

    obName = arg;

    ob = present(obName, this_player());

    if(!ob)
    {
        return(notify_fail("The object '" + obName + "' can not be found.\n"));
    }

    if(!ob->is_equipped()) 
    {
        // just to be safe
        this_player()->remove_object_from_slots( ob );

        return(notify_fail("The object '" + obName + "' is not equipped\n"));    
    }

    if(!this_player()->remove_object_from_slots( ob ) )
    {
        return(notify_fail("Error when removing the object!" ) );
    }

    write("You remove a " + ob->query_short() + "\n");
    say(capitalize(this_player()->query_name()) + " removes a '" + ob->query("short") + "'.\n");

    return 1;
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "remove <item>\n\n"
      "This command allows the user to remove equipped objects.\n"
      HIW + "See also: " + NOR + "wear\n");
}
