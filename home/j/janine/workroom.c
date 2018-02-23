//
//  /home/j/janine/workroom.c
// GB MUD


inherit ROOM;

void create()
{
    ::create();
    
    set_light(1);
    set_short("Janine's workroom");
    set_long(
             "The little room is painted sage green and has soft, indirect\n"
             "lighting.  A big cushy armchair sits inone corner with a small\n"
             "table just next to it.  There is a gleaming 17 inch silver\n"
             "laptop on the table.  A coffee pot putters away in the corner.\n"
             );
    set_exits( ([
                 "cafe" : "/areas/lpuni/entrance.c",
                 "void" : "/areas/std/void.c",
                 "demo" : "/areas/demo/demo1.c",
                 "lab"  : "/home/j/janine/lab.c"
                 ]) );
    set_items( ([
                 "sign" : "The sign reads:\n"
                 "'You are never given a wish without also being given the\n"
                 "power to make it come true. You may, however, have to work for\n"
                 "it.'\n",
                 ]) );
}
