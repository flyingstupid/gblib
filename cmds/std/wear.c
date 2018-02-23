/* wear.c

 emraef @ gbmud
 28-FEBRUARY-12
 Standard Command

*/
inherit COMMAND;
int main(string arg)
{
    object ob;
    string loc;
    string obName;

    if(!arg)
    {
        return(notify_fail("SYNTAX: wear <item> [location]\n"));
    }

    if( sscanf( arg, "%s %s", obName, loc ) != 2 )
    {
        obName = arg;
    }

    ob = present(obName, this_player());

    if(!ob)
    {
        return(notify_fail("The object '" + obName + "' can not be found.\n"));
    }

    if(!ob->can_be_equipped())
    {
        return(notify_fail("The object '" + obName + "' can not be worn.\n"));
    }

    if(ob->is_equipped()) 
    {
        return(notify_fail("The object '" + obName + "' is already equipped\n"));    
    }

    if(!ob->is_valid_wear_loc( loc ) )
    {
        loc = ob->get_default_wear_loc();
    }

    if(!this_player()->set_object_in_slot( ob, loc ) )
    {
        return(notify_fail("Error when wearing the object! loc: " + loc + "\n" ) );
    }

    write("You wear a " + ob->query_short() + "\n");
    say(capitalize(this_player()->query_name()) + " wears a '" + ob->query("short") + "'.\n");

    return 1;
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "wear <item> [location]\n\n"
      "This command allows the user to wear some kinds of objects.\n"
      "The user can optionally specify a location if the item can be\n"
      "worn on multiple locations\n"
      HIW + "See also: " + NOR + "remove\n");
}
