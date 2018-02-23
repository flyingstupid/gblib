/* look.c


 Tacitus @ LPUniversity
 06-Oct-06 
 Look Command (Rewrite # ... 3?)

 Last updated on January 22nd, 2007 by Tricky @ RtH
 
 --------------------------------------------------
 
 I added some error stuff for GMs to be able to get some info on the fly without a ton of trouble!
 
 -Critical
 
 
*/
inherit COMMAND;
object room;

int render_room();
int render_object(string target);
int render_container(string target);
string damage_display(object target);
string highlight_view(string str, string *keys);

int main(string arguments)
{
    string target;
    
    room = environment(this_player());
    
    if( !arguments )
    {
        return render_room();
    }
    else if( sscanf( arguments, "at %s", target ) )
    {
        return render_object( lower_case( target ) );
    }
    else if(sscanf(arguments, "in %s", target))
    {
        return render_container( lower_case( target ) );
    }

    return render_object(arguments);
}

string highlight_view(string str, string *items)
{
    if( sizeof( items ) <= 0 )
    {
        return str;
    }

    foreach(string item in items)
    {
        mixed array assoc;

        assoc = reg_assoc(" " + str, ({ "[^A-Za-z0-9]+(" + item + ")+[^A-Za-z0-9]+" }), ({ 1 }) );

        for(int l = 0; l < sizeof(assoc[0]); l++)
        {
            if(assoc[1][l])
            {
                assoc[0][l] = replace_string(assoc[0][l], item, "" + item + "");
            }
        }

        str = implode(assoc[0], "")[1..<1];
    }

    return str;
}

int render_exits()
{
    string *exits;

    exits = keys(room->query_exits());

    switch(sizeof(exits))
    {
        case 0:
        {
            write(CYN + "There are no obvious exits here." + NOR + "\n\n");
            break;
        }
        case 1:
        {
            write(CYN + "The only obvious exit is " + HIY + exits[0] + NOR + CYN + "." + NOR + "\n\n"); 
            break;
        }
        default:
        {
            write(CYN + 
              sprintf("The only obvious exits are %s and %s.",
                HIY + implode(exits[0..<2], NOR + CYN + ", " + HIY) + NOR + CYN,
                HIY + exits[<1] + NOR + CYN,
              ) + NOR + "\n\n"
            );
        }
    }

    if( !wizardp( this_user() ) )
    {
        return 1;
    }
    
    exits = keys(room->query_ghostExits());

    switch(sizeof(exits))
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            write(RED + "The only ghost exit is " + HIG + exits[0] + NOR + RED + "." + NOR + "\n\n"); 
            break;
        }
        default:
        {
            write(CYN + 
              sprintf("The ghost exits are %s and %s.",
                HIG + implode(exits[0..<2], NOR + RED + ", " + HIG) + NOR + RED,
                HIG + exits[<1] + NOR + RED,
              ) + NOR + "\n\n"
            );
        }
    }

    return 1;
}

int render_room()
{
    if(!objectp(room)) 
    {
        return notify_fail("You see nothing because you have no environment!\n");
    }

    if( room )
    {
        tell_object( this_user(), room->vmap() + "\n" );
    }

    return 1;   
}

int render_object(string target)
{
    object ob, user;
    string subtarget;

    if(stringp(room->query_item(target)))
    {
        write(
          highlight_view(
            room->query_item(target),
            keys(room->query_items()) - ({ target })
          ) + "\n");

        return 1;
    }

    if(sscanf(target, "%s in %s", target, subtarget) == 2 || 
        sscanf(target, "%s on %s", target, subtarget) == 2 && subtarget != "me")
    {
        user = present(subtarget, room);
        if(!objectp(user)) return notify_fail("You can not find '" + subtarget
            + "'.\n");
        ob = present(target, user);
    }
    else
    {
        ob = present(target, room);
        if(!objectp(ob)) ob = present(target, this_player());
    }

    if(!objectp(ob)) return notify_fail("You can't find '" + target + "'.\n");

    if(living(ob))
    {
        object *inv = all_inventory(ob);

        if(ob == this_player())
        {
            write("You look at yourself.\n");
            tell_room(room, this_player()->query_cap_name() 
                + " looks at themselves.\n", ({ ob }));

            write("\t" + ob->query_cap_name() + "\n\n");
            write(ob->query_long() + "\n");
            write(implode(filter(inv->query("extra_look"), (: $1 :)),
                "\n") + "\n\n");

            if(sizeof(inv) <= 0) write("You are carrying nothing.\n\n");
            else write("You are carrying:\n" + implode(inv->query_short(), 
                "\n") + "\n\n");
        }
        else
        {
            write("You look at " + ob->query_cap_name() + ".\n");
            tell_room(room, this_player()->query_cap_name() + " looks at " +
                ob->query_cap_name() + ".\n", ({ this_player(), ob }) );
            tell_object(ob, this_player()->query_cap_name() + " looks at you.\n");

            write("\t" + ob->query_cap_name() + "\n\n");
            write(ob->query_long() + "\n");
            write(implode(filter(inv->query("extra_look"), (: $1 :)),
                "\n") + "\n\n");

                
                //If its a ghost AND your a Wizard, then tell us ALL of your ghost INFO!
                if(ob->IsGhost() && wizardp(this_player()))
                {
                    write("%^BOLD%^BLACK%^--------Admin Info--------\n");
		    write("%^BOLD%^BLACK%^Ghost Class = "+ ob->GetGhostClass() + "\n");
		    write("%^BOLD%^BLACK%^Ghost Power = "+ ob->GetGhostPower() + "\n");
		    write("%^BOLD%^BLACK%^Ghost Freq  = "+ ob->GetFrequency()  + "\n");
		    write("%^BOLD%^BLACK%^--------------------------%^RESET%^\n");
                }
                
                
                
                
                
                //Show player damage when you look at them.
                if(ob->IsGhost())
                {
                    write(ob->query_cap_name() + " is immaterial\n");
                }
                else
                {
                    write(ob->query_cap_name() + " is " + damage_display(ob) + "\n");
                }
                                
                //Show Player Statuses
                if(ob->CheckForStatus("slimed"))
                {
                    write(ob->query_cap_name() + " is covered in %^GREEN%^slime!%^RESET%^\n");
                }

            if(sizeof(inv) <= 0) write(ob->query_cap_name() 
                + " is carrying nothing.\n\n");
            else write(ob->query_cap_name() + " is carrying:\n" 
                + implode(inv->query_short(), "\n") + "\n\n");
        }

    }
    else
    {

        if(objectp(user))
        {
            write("You look at a " + ob->query_short() + " on "
                + user->query_cap_name() + "\n\n");
            tell_object(user, this_player()->query_cap_name() 
                + " looks you over.\n");
            tell_room(room, this_player()->query_cap_name() +
                " looks over " + ob->query_short() + "\n",
                ({ this_player(), user }));
        }
        else
        {        
            write("You look at a " + ob->query_short() + "\n\n");
            tell_room(room, this_player()->query_cap_name() + " looks at "
                + ob->query_short() + "\n", ({ this_player() }) );
        }

        write(ob->query_long() + "\n");        
    }  

    return 1;
}

int render_container(string target)
{
    return notify_fail("Error: Containers are not implemented yet.\n");
}

string damage_display(object target)
{
    object player;
    player=target;
        
    if(player->get_health()==100)
    {
        return("Healthly");
    }

    if(player->get_health()>79 && player->get_health()<100)
    {
        return("Grazed");
    }

    if(player->get_health()>59 && player->get_health()<80)
    {
        return("Hurt");
    }

    if(player->get_health()>39 && player->get_health()<59)
    {
        return("Injured");
    }

    if(player->get_health()>19 && player->get_health()<40)
    {
        return("Crippled");
    }

    if(player->get_health()>0 && player->get_health()<20)
    {
        return(RED + "Dying" + NOR);
    }
}


string help()
{
    return(HIW + " SYNTAX:" + NOR + " look [<in/at>] <object> [<on/in> <object>]\n\n" +
      "This command will allow you to look at objects in your environment.\n" +
      "If no command is supplied, it will show you the whole room. You can\n" +
      "also look at specific objects by typing 'look <object>' or 'look at object'.\n" +
      "You might also try looking into an object by type 'look in <object>'.\n");
}

