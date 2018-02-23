/* overrides.c
 *
 * Tacitus @ LPUniversity
 * 08-APR-05
 * Simul-efuns
 *
 */

int exec(object to, object from)
{
    if (adminp(previous_object()))
        return efun::exec(to, from);
    else return 0;    
}

/* Function name: destruct
 * Description:   The destruct simul_efun guarantees that an object will
 *                always have remove() called in it if it is destructed
 *                by another object.  destruct() with no arguments
 *                destructs this_object WITHOUT calling remove, which is
 *                the correct way to destruct an object from within a
 *                remove() function.
 */
varargs void destruct(object ob)
{
    mixed array previous_functions = call_stack(2);

    if (previous_functions[0] == "remove")
    {
        if (!objectp(ob)) ob = previous_object();

        efun::destruct(ob);
        return;
    }

    if (objectp(ob)) catch(ob->remove());
    else ob = previous_object();

    if (objectp(ob)) efun::destruct(ob);
}

void shutdown(int how)
{
    if (file_name(previous_object()) == "/adm/daemons/shutdown_d")
        efun::shutdown(how);
}

void set_privs(object ob, string privs)
{
    string name;
     
    if (adminp(previous_object()) || ob = master())
        efun::set_privs(ob, privs);

    sscanf(file_name(ob), "/home/%*s/%s/%*s", name);

    if (name == privs) efun::set_privs(ob, privs);
}

object query_snoop(object ob)
{
    if (adminp(previous_object()) || previous_object() == master())
        return efun::query_snoop(ob);

    return 0;
}

object query_snooping(object ob)
{
    if (adminp(previous_object()) || previous_object() == master())
        return efun::query_snooping(ob);

    return 0;
}

varargs object snoop(object snooper, object snoopee)
{
    if (adminp(previous_object()) || previous_object() == master())
    {
        if (!snoopee)
            return efun::snoop(snooper);
        else
            return efun::snoop(snooper, snoopee);
    }

    return 0;
}

int living(object ob)
{
    string temp;

    sscanf(file_name(ob), "%s#%*s", temp);

    if (!temp) temp = file_name(ob);

    if( temp == MOBILE )
    {
        return 1;
    }

    return inherits( MOBILE, ob );
}

object *livings()
{
    object *retArray;

    retArray = ({});

    foreach( object ob in objects() )
    {
        if( living( ob ) )
        {
            retArray += ({ ob });
        }
    }

    return retArray;
}

/* Overridden to allow us to find mobiles using alternate ID's. */
object find_living(string str)
{
    object ob, here;

    if (!stringp(str) || str == "") return 0;
    if (objectp(this_user())) ob = this_user();
    else ob = previous_object();

    here = environment(ob);

    if (objectp(here))
    {
        object array npcs = filter(all_inventory(here), (: $1 != $2 && living( $1 ) :), ob);

        foreach (object npc in npcs)
            if (npc->id(str)) return npc;
    }

    foreach (object living in livings())
        if (living->id(str)) return living;

    return 0;
}

int notify_fail( mixed input )
{
    efun::notify_fail( input );
    return 0;
}

object this_user()
{
    return efun::this_user();;
}

object this_player()
{
    return this_user();
}

object this_interactive()
{
    return efun::this_user();
}

void tell_room( mixed env, string str,object array exc )
{
    if( !arrayp( exc ) )
    {
        exc = ({ exc });
    }

    env->write_to_room( str, exc );
}

void say( string str )
{
    object tp = this_user();
    
    if( !tp )
    {
        return;
    }

    tell_room( environment( tp ), str, ({ tp }) );
}

void write( string str )
{
    object tp = this_user();
    
    if( !tp )
    {
        return;
    }

    tell_object( tp, str );
}

object present( mixed str, object invOb )
{
    array inv;
    object ob;
    int invIndex;


    if( undefinedp( invOb ) )
    {
        invOb = previous_object();
    }

    inv = invOb->get_inventory( this_user() );
    
    if( objectp( str ) )
    {
        invIndex = member_array( str, inv );
        if( invIndex == -1 )
        {
            return 0;
        }

        return inv[invIndex];
    }

    if( !inv )
    {
        return 0;
    }

    foreach( ob in inv )
    {
        if( ob->id( str ) )
        {
            return ob;
        }
    }

    return 0;
}




#ifdef __FLUFFOS__
/* Function name: format_mixed
 * Description:   This is an updated version of identify found in the
 *                Dead Souls lib. Cratylus has given permission for it to be
 *                included here.
 *                New features include class disassembly and buffer
 *                disassembly.
 * Author:        Tricky
 */
/* Original header from Dead Souls */
/*    /secure/sefun/identify.c
 *    from the Dead Souls LPC Library
 *    represent a variable of any type as a string, now out of date
 *    remains for backwards compat
 *    created by Pallando@Dead Souls (Douglas Reay) 921212
 */
string format_mixed(array args...);

privatef string f_format_mixed(mixed mixvar)
{
    int sz;
    string ret;

    if (undefinedp(mixvar)) return "UNDEFINED";
    if (intp(mixvar)) return "" + mixvar;
    if (floatp(mixvar)) return "" + mixvar;
    if (objectp(mixvar))
    {
        if (ret = mixvar->query_name()) ret += " ";
        else ret = "";

        return "OBJECT(" + ret + file_name(mixvar) + ")";
    }
    if (stringp(mixvar))
    {
        mixvar = replace_string(mixvar, "\"", "\\\"");
        mixvar = "\"" + mixvar + "\"";
        mixvar = replace_string(mixvar, "\\", "\\\\");
        mixvar = replace_string(mixvar, "\\\"", "\"");
        mixvar = replace_string(mixvar, "\n", "\\n");
        mixvar = replace_string(mixvar, "\t", "\\t");

        return mixvar;
    }
    if (arrayp(mixvar))
    {
        ret = "ARRAY({ ";
        sz = sizeof(mixvar);

        for (int i = 0 ; i < sz ; i++)
        {
            if (i != 0) ret += ", ";

            ret += format_mixed(mixvar[i]);
        }

        return ret + (sz != 0 ? " " : "") + "})";
    }
    if (bufferp(mixvar))
    {
        ret = "BUFFER({ ";
        sz = sizeof(mixvar);

        for (int i = 0 ; i < sz ; i++)
        {
            if (i != 0) ret += ", ";

            ret += format_mixed(mixvar[i]);
        }

        return ret + (sz != 0 ? " " : "") + "})";
    }
    if (classp(mixvar))
    {
        ret = "CLASS(/ ";
        mixvar = disassemble_class(mixvar);
        sz = sizeof(mixvar);

        for (int i = 0 ; i < sz ; i++)
        {
            if (i != 0) ret += ", ";

            ret += format_mixed(mixvar[i]);
        }

        return ret + (sz != 0 ? " " : "") + "/)";
    }
    if (mapp(mixvar))
    {
        mixed ks, vs;

        ret = "MAPPING([ ";
        ks = keys(mixvar);
        vs = values(mixvar);
        sz = sizeof(ks);

        for (int i = 0 ; i < sz ; i++)
        {
            if (i != 0) ret += ", ";

            ret += format_mixed(ks[i]) + ": " + format_mixed(vs[i]);
        }

        return ret + (sz != 0 ? " " : "") + "])";
    }
    /* We don't want to set-up a recursive loop here :) */
    if (functionp(mixvar)) return efun::sprintf("FUNCTION(%O)", mixvar);

    return "UNKNOWN";
}

/* This can be made private to the simul_efun object only.
 * I am leaving it publically available to the lib for
 * backwards compatibility reasons. Tricky.
 */
string format_mixed(array args...)
{
    string array ret = ({ });
    int sz = sizeof(args);

    if (sz == 0)
    {
        /* Return UNDEFINED_VALUE for empty argument list. */
        ret = ({ f_format_mixed(UNDEFINED_VALUE) });
    }
    else if (sz == 1)
    {
        ret = ({ f_format_mixed(args[0]) });
    }
    else
    {
        for (int i = 0 ; i < sz ; i++)
        {
            ret += ({ f_format_mixed(args[i]) });
        }
    }

    return implode(ret, ", ");
}

/* (s)printf overrides to change the format of %O */
string sprintf(string format, array args...)
{
    int i, j, num = 0, sz_format = strlen(format);

    for (i = 0 ; i < sz_format ; i++)
    {
        int token = 0;

        if (format[i] == '%')
        {
            j = i + 1;

            while (!token)
            {
                switch (format[j])
                {
                    case '\'':
                        j++;
                        j += strsrch(format[j..<1], '\'') + 1;
                        break;
                    case '*':
                        num++;
                        j++;
                        break;
                    case '%':
                    case 'O':
                    case 's':
                    case 'd':
                    case 'i':
                    case 'c':
                    case 'o':
                    case 'x':
                    case 'X':
                    case 'f':
                        token = 1;
                        break;
                    default: j++;
                }

                i++;
            }
        }

        if (token && format[j] != '%')
        {
            if (format[j] == 'O')
            {
                format[j] = 's';
                args[num] = format_mixed(args[num]);
            }

            num++;
        }
    }

    return efun::sprintf(format, args...);
}

void printf(string format, array args...)
{
    write(sprintf(format, args...));
}
#endif
