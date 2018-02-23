inherit OBJECT;
string set_date();

void create()
{
     set_id(({"mirror", "glass"}));
         set_short("A cracked mirror");
         set_long("Between the spiderweb of shattered glass you see hundreds of " +this_player()->query_cap_name() +"s\n"+
              "starring back at you.\n"
                 );
        set("prevent_get", 1);
}
