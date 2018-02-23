/* clone.c

 Tacitus @ LPUniversity
 31-OCT-05
 Standard object minipulation command

*/

//Last edited on July 19th, 2006 by Parthenon
inherit COMMAND;
int main(string str)
{
    object ob;
    string err, custom, tmp;
    int power;
    string filename;

    if(!str || sscanf( str, "%s %d", filename, power ) != 2 )
        return(notify_fail("SYNTAX: makeghost <filename> <power>\n"));

    if( power == 0 )
        power = 1;

    if(filename[<2..<1] != ".c")
        filename += ".c";

    filename = resolve_path(this_player()->query("cwd"), filename);

    if(!file_exists(filename)) return(notify_fail("Error [clone]: Unable to find file '" + filename + "'.\n"));     

    write("Notice [clone]: Cloning file '" + filename + "' to environment...\n");
    err = catch(ob = clone_object(filename));

    if(stringp(err) || !ob)

    if( is_a( GHOST, ob ) == 0 )
    {
        destruct( ob );
        return(notify_fail("Error [clone]: An error was encountered when cloning the object:\n" + "  Not of ghost type"  + "\n"));
    }

    ob->move(environment(this_player()));
    ob->SetGhostPower(power);

    if(this_player()->query_env("custom_clone") && wizardp(this_player()))
	custom = this_player()->query_env("custom_clone");

    if(custom)
    {
        tmp = custom;
        tmp = replace_string(tmp, "$O", (ob->query_short()[0] == 'a' ? ob->query_short() : "a " + ob->query_short()));
        tmp = replace_string(tmp, "$N", this_player()->query_cap_name());
        tell_room(environment(this_player()), capitalize(tmp) + "\n", this_player());
        write("Success [clone]: New object '" + file_name(ob) + "' cloned.\n");
    }
    else
    {
        write("Success [clone]: New object '" + file_name(ob) + "' cloned.\n");
        tell_room(environment(this_player()), 
            capitalize(this_player()->query_name()) + " creates a '" + ob->query_short() + "'.\n", 
            ({this_player()}));
    }

    return 1;
}

string help() {
    return (HIW + " SYNTAX: " + NOR + "clone <file>\n\n" + 
      "This command produces a clone of a file.\n\n" +
      HIW + "See also: " + NOR + "dest");
}     




