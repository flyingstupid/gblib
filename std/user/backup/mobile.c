/* mob.c

 Tacitus @ LPUniversity
 11-JUNE-06
 Character Object

*/

/* This object represents a charachter in the mud.
 Another object that inherits this represents NPCs
 */

/* Last edited by Tacitus on October 4th, 2006 */

#include <config.h>
#include <driver/origin.h>
#include <logs.h>

inherit OBJECT;
inherit "/std/user/user/alias.c";

/* Global Variables */

private string *commandHistory = ({});
private object link;
string *path;
string *Earmuffed;
string title;
string pretitle;
private int hb_time;



/* Prototypes */

/* Connection functions */

void setup();
void enter_world();
void exit_world();
void net_dead();
void reconnect();

/* User object functions */

varargs int move(mixed ob, int flag);
void restore_user();
void save_user();
void remove();
object query_link();
int set_link(object ob);

/* User environmental variable functions */

int set_env(string var_name, string var_value);
mixed query_env(string var_name);
mapping list_env();

/* User path functions */

string *query_path();
void add_path(string str);
void rem_path(string str);

/* Communication & Interaction functions */

void catch_tell(string message);
void receive_message(string type, string msg);
mixed process_input(string arg);
int commandHook(string arg);
mixed* query_commands();
int force_me(string cmd);
int command( string str );

/* Misc functions */

void set_title(string str);
void set_pretitle(string str);
string query_title();
string query_pretitle();
void write_prompt();

/* Functions */

void create()
{
    if (origin() != ORIGIN_DRIVER && origin() != ORIGIN_LOCAL) return;
    path = ({ "/cmds/std/", "/cmds/demo/" });
}

/* Connection functions */

void setup()
{
    set_ids(({query_name()}));
    set_name(query_name());
    set_heart_beat(1);
    set("prevent_get", 1);
    hb_time = 0;

    if (!query("cwd")) set("cwd", "/doc");
    if (!query("cwf")) set("cwf", "");
    if (!query_long()) set_long(capitalize(query_name()) + "");
    if (!mapp(query("env_settings")))
        set("env_settings", (["colour" : "enabled"]));
    if (!query_env("news_client"))
        set_env("news_client", "/obj/mudlib/newsclients/std_newsclient.c");
    if (!query_env("auto_tune")) set_env("auto_tune", "all");
    if (!query_env("biff")) set_env("biff", "on");
    if (!query_env("keepalive")) set_env("keepalive", " \b");
    if (!query_env("prompt")) set_env("prompt", ">");
    if (!arrayp(Earmuffed)) Earmuffed = ({ });
}

void enter_world()
{
    string *cmds, *ch;
    int i;
    object news_client, mail_client;

    if (!isMember(query_privs(previous_object()), "admin")) return;

    ANNOUNCE_CHDMOD->announce_login(query_name());

    catch
    {
        news_client = new(query_env("news_client"));
        news_client->move(this_object());
        if (news_client->isNew())
            write("\n" + HIG + "Notice:" + NOR + " There are new news posts.\n\n");
        destruct(news_client);
        mail_client = new(OBJ_MAIL_CLIENT);
        mail_client->move(this_object());
        mail_client->init();
        if (mail_client->has_new_mail())
            write(HIC + "You have new mail!" + NOR + "\n\n");
        destruct(mail_client);
    };

    catch
    {
       ch = explode(query_env("auto_tune"), " ");

       if (sizeof(ch) > 0)
           foreach (string channel in ch)
              force_me("channel tune in " + channel);
    };

    if (file_size(user_path(query_name()) + ".login") > 0)
    {
        write("\n");
        cmds = explode(read_file(user_path(query_name()) + ".login"), "\n");
        if (sizeof(cmds) <= 0) return;
        for (i = 0 ; i < sizeof(cmds) ; i ++) catch(command(cmds[i]));
    }

    set("last_login", time());
    write("\n");
    say(capitalize(query_name()) + " has entered.\n");
}

void exit_world()
{
    string *cmds;
    int i;

    if (this_player() != this_object()) return;
    if (file_size(user_path(query_name()) + ".quit") > 0)
    {
        cmds = explode(read_file(user_path(query_name()) + ".quit"), "\n");
        if (sizeof(cmds) <= 0) return;
        for (i = 0 ; i < sizeof(cmds) ; i ++) catch(command(cmds[i]));
    }

    set("last_login", time());

    if (environment(this_player()))
        say(capitalize(query_name()) + " leaves " + mud_name() + ".\n");

    ANNOUNCE_CHDMOD->announce_logoff(query_name());
    save_user();
}

void net_dead()
{
    if (origin() != ORIGIN_DRIVER) return;

    set("last_login", time());
    save_user();

    if (environment(this_object()))
        tell_room(
          environment(this_object()),
          capitalize(query_name()) + " has gone link-dead.\n"
        );

    log_file(LOG_LOGIN, capitalize(query_name()) + " went link-dead on " + ctime(time()) + "\n");
}


void reconnect()
{
    restore_user();
    set("last_login", time());
    write("Success: Reconnected.\n");

    if (environment(this_object()))
        tell_room(
          environment(this_object()),
          capitalize(query_name()) + " has reconnected.\n",
          this_player()
        );

    /* reconnection logged in login object */
}

/* User Object Functions */

void heart_beat()
{
    if(!interactive(this_object()) && !devp(this_object()))
    {
        if((time() - query("last_login")) > 3600)
        {
            if(environment(this_object()))
                tell_room(environment(this_object()), capitalize(query_name()) +
                  " fades out of existance.\n");
            log_file(LOG_LOGIN, capitalize(query_name()) + " auto-quit after 1 hour of net-dead at " + ctime(time()) + ".\n");
            destruct(this_object());
        }
    }
    else
    {
        /* Prevent link-dead from idle */
        if(query_idle(this_object()) % 60 == 0 && query_idle(this_object()) > 300
                && query_env("keepalive") && query_env("keepalive") != "off")
        {
            string keepAliveString = query_env("keepalive");
            
            keepAliveString = replace_string(keepAliveString, "%0", "\0");
            keepAliveString = replace_string(keepAliveString, "%n", "\n");
            keepAliveString = replace_string(keepAliveString, "%b", "\b");
            keepAliveString = replace_string(keepAliveString, "%t", ctime(time()));
            
            write(keepAliveString);
        }

        hb_time++;

        if (hb_time >= 60)
        {
            hb_time = 0;
            save_user();
        }
    }
}

void restore_user()
{
    if(!isMember(query_privs(previous_object() ? previous_object() : this_player()), "admin") && this_player() != this_object()) return 0;
    if(isMember(query_privs(previous_object()), "admin") || query_privs(previous_object()) == this_player()->query_name()) restore_object(user_mob_data(query_name()));
}

void save_user()
{
    if(!isMember(query_privs(previous_object() ? previous_object() : this_player()), "admin") && this_player() != this_object()) return 0;
    catch(save_object(user_mob_data(query_name())));
}

varargs int move(mixed ob, int flag)
{
    if(!::move(ob)) return 0;
    set("last_location", get_base(ob));
    if(!flag)
    {
        if( query_env( "automap" ) )
        {
            command("vmap");
        }
        else
        {
            command("look");
        }
    }
    return 1;
}

void remove()
{
    if(objectp(query_link())) destruct(query_link());
    ::remove();
}

object query_link()
{
    return link;
}

int set_link(object ob)
{
    if(query_privs(previous_object()) != query_privs(this_object())
        && !adminp(previous_object())) return 0;
    link = ob;
    return 1;
}

/* Environmental Settings */

int set_env(string var_name, string var_value)
{
    mapping data = query("env_settings");
    if(!var_value) map_delete(data, var_name);
    else data += ([var_name : var_value]);
    set("env_settings", data);
    return 1;
}

mixed query_env(string var_name)
{
    mapping data = query("env_settings");
    if(!sizeof(data)) return 0;
    if(!data[var_name]) return 0;
    return data[var_name];
}

mapping list_env()
{
    mapping data = query("env_settings");
    return data;
}


/* User path functions */

string *query_path()
{
    return copy(path);
}

void add_path(string str)
{
    if(!adminp(previous_object()) && this_player() != this_object()) return;
    
    if(member_array(str, path) != -1)
    {
        write("Error [path]: Directory '" + str + "' is already in your path.\n");
        return;
    }
    
    if(str[<1] != '/') str += "/";
    
    if(!directory_exists(str))
    {
        write("Error [path]: Directory '" + str + "' does not exist.\n");
        return;
    }
    
    path += ({str});
}

void rem_path(string str)
{
    if(!adminp(previous_object()) && this_player() != this_object()) return;
    
    if(member_array(str, path) == -1)
    {
        write("Error [path]: Directory '" + str + "' is not in your path.\n");
        return;
    }
    
    path -= ({str});
}

/* Communication & Interaction functions */

void catch_tell(string message)
{
    receive_message("unknown", message);
}

void receive_message(string type, string msg)
{
    object termd;
    string array imud_listen = ({ });
    int ignore_ansi = 0;

    ignore_ansi = !(query_env("color") == "enabled"
      || query_env("colour") == "enabled");

    if (query_env("imud_listen"))
        imud_listen = explode(query_env("imud_listen"), " ");

    switch (type)
    {
        case "intermud-error":
        case "intermud-warning":
        case "intermud-finger":
        case "intermud-locate":
        case "intermud-who":
        {
            if (sizeof(imud_listen) < 1) return;
            if (member_array(type[9..<1], imud_listen) == -1) return;
            break;
        }
        case "ignore_ansi":
        {
            ignore_ansi = 1;
            break;
        }
        case "unknown":
        default:
            break;
    }

    if (type == "eval") msg = replace_string(msg, "%^", "%%^^");

    if (objectp(termd = find_object(TERMINAL_D)))
    {
        string term;
        int wrap, indent;

        term = termd->query_user_term(this_object());
        wrap = termd->query_user_width(this_object());
        indent = termd->query_user_indent(this_object());

        if (ignore_ansi)
            msg = termd->parse_pinkfish(msg, 1, wrap, indent);
        else msg = termd->parse_pinkfish(msg, term, wrap, indent);
    }
   
    while( sizeof( msg ) > MAX_PRINT_STRING )
    {
        receive(msg[0..MAX_PRINT_STRING-1]);
        msg = msg[(MAX_PRINT_STRING)..];
    }
    receive(msg);
}

mixed process_input(string commandLine)
{
    return commandLine;
}

nomask varargs string *query_commandHistory(int index, int range)
{
    if (this_player() != this_object() && !adminp(previous_object()))
        return ({ });
    if (!index) return commandHistory + ({ });
    else if (range) return commandHistory[index..range] + ({ });
    else return ({ commandHistory[index] });
}

mixed* query_commands()
{
    return ({});    
}

int force_me(string cmd)
{
    if(!isMember(query_privs(previous_object()), "admin")) return 0;
    else command(cmd);
}

//Misc functions

void set_title(string str)
{
     title = str;
     set("title", str);
}

string query_title()
{
     if (!title) return query("title");
     return title;
}

void set_pretitle(string str)
{
     pretitle = str;
     set("pretitle", str);
}

string query_pretitle()
{
     if (!pretitle) return query("pretitle");
     return pretitle;
}

string query_short()
{
    string str = ::query_short();

    if (!str) str = "$N";
    if (strsrch(str, "$N") == -1
     && strsrch(lower_case(str), lower_case(query_name())) == -1)
        str = "$N";

    str = replace_string(str, "$N", capitalize(query_name()));

    if (!interactive(this_object()) && member_array(this_object(), users()) != -1)
        str = "A statue of " + str;

    return str;
}


void add_earmuffed(mixed earmuffs)
{
    string *tmp;

    if (stringp(earmuffs)) earmuffs = ({ earmuffs });
    else if (!arrayp(earmuffs)) return;

    earmuffs = map(earmuffs, (: lower_case($1) :));

    if (!arrayp(Earmuffed)) Earmuffed = ({ });

    tmp = Earmuffed - earmuffs;
    Earmuffed = tmp + earmuffs;
}

void remove_earmuffed(mixed earmuffs)
{
    if (stringp(earmuffs)) earmuffs = ({ earmuffs });
    else if (!arrayp(earmuffs)) return;

    earmuffs = map(earmuffs, (: lower_case($1) :));

    if (!arrayp(Earmuffed)) Earmuffed = ({ });

    Earmuffed -= earmuffs;
}

void set_earmuffed(mixed earmuffs)
{
    if (stringp(earmuffs)) earmuffs = ({ earmuffs });
    else if (!arrayp(earmuffs)) return;

    earmuffs = map(earmuffs, (: lower_case($1) :));

    if (!arrayp(Earmuffed)) Earmuffed = ({ });

    Earmuffed = earmuffs;
}

string *query_earmuffed()
{
    if (!arrayp(Earmuffed)) Earmuffed = ({ });

    return copy(Earmuffed);
}

string query_prompt( string prompt )
{
    if( !prompt )
    {
        prompt = query_env( "prompt" );
    }

        catch
        {
            if(devp(this_object()))
            { 
                    prompt = replace_string(prompt, "%d",
                        ((query("cwd")[0..(strlen(user_path(query_name())) - 1)] ==
                             user_path(query_name()) ) ? "~/" +
                             query("cwd")[(strlen(user_path(query_name())))..] : query("cwd")));
                    prompt = replace_string(prompt, "%f",
                        (query("cwf")[0..(strlen(user_path(query_name())) - 1)] ==
                             user_path(query_name()) ) ? "~" +
                             query("cwf")[strlen(user_path(query_name()))..] : query("cwf"));
                    prompt = replace_string(prompt, "%u", "" + sizeof(users()));
                    prompt = replace_string(prompt, "%l", file_name(environment(this_player())));
            }

            prompt = replace_string(prompt, "%n", query_cap_name());
            prompt = replace_string(prompt, "%m", mud_name());
            prompt = replace_string(prompt, "%T", ctime(time())[11..18]);
            prompt = replace_string(prompt, "%t", ctime(time())[11..15]);
            prompt = replace_string(prompt, "%d", ctime(time())[4..10]);
            prompt = replace_string(prompt, "%D", ctime(time())[0..10]);
            prompt = replace_string(prompt, "$n", "\n");
        };

    return prompt;
}

void write_prompt()
{
    write( query_prompt( 0 ) + " " );
}

int command( string str )
{
    return time_expression{ process_input( str ); };
}
