/* /std/area/mobiles/npc.c
 
 Tacitus @ LPUniversity
 28-JUNE-06
 Non-player character
 
 */

inherit MOBILE;


/* Ask command functions*/
int setReplies( mapping replies );
void addReply(string query, string reply);
string getReply(string key);



/*Ask Variable*/
mapping replies = ([]);



void setup();

void create()
{
    ::create();
    
    path = ({ "/cmds/npc/", "/cmds/std/", "/cmds/demo/" });
    
    set("prevent_get", 1);
    if(!query("cwd")) set("cwd", "/doc");
    if(!mapp(query("env_settings"))) set("env_settings", (["colour" :
                                                           "enabled"]));
    if(!query_env("news_client")) set_env("news_client",
                                          "/obj/mudlib/newsclients/std_newsclient.c");
    if(!query_env("auto_tune")) set_env("auto_tune", "localNet");
    setup();
    
}

void setup()
{
    set_name("Generic NPC");
    set_ids(({query_name(), "npc", "generic npc", "NPC" }));
    if(clonep(this_object())) set_heart_beat(1);
    set_long(capitalize(query_name()) + " is a generic NPC.");
    set_short(query_name());
    ::setup();
}

//int commandHook(string arg)
//{
//      return :: commandHook(arg);
//}

void restore_user()
{
    return;
}

void save_user()
{
    return;
}

int force_me(string cmd)
{
    command(cmd);
}

void heart_beat()
{
    return;
}

/**
 * Ask command functions
 * 
 * Allocating and returning Ask Mapping
 */

/* Creates a map for NPC replies to the ask command */
int setReplies( mapping reply )
{
    replies = reply;
    set("replies", reply);
    return 1;
}

/* adds responses to the repies map*/
int add_reply( string query, string reply ){
    replies += ([query : ({reply}) ]);
    set("replies", reply);
    return 1; 
}

/* returns the reply to an inquery of 'key'*/
string query_reply(string query)
{
    write ("thinkig....");
    if(sizeof(replies) < 1)
    {
        write ("This person doesn't have anything to say");
        return 0;
    }
    if (replies[query]){
        write ("This person thinks carefully");
        return replies[query];
    }
    write( "This person doesn't know about that");
    return 0;
}
