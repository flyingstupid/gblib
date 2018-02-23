//  /areas/demo/demo1.c

inherit ROOM;

void create()
{
    set_light(1);
    set_short("Ready Room");
    set_long(
             "This is the ready room. Lining the walls are proton packs,\n"
             "PKE meters and ghost traps. There is a single door that leads\n"
             "too your first combat with the post-life entities. Get Ready!\n"
             );
    set_exits( ([
                 "out" : ({ "/areas/demo/demo2"}),
                 "chargen" : ({"/areas/demo/demo6"}),
                 "street"  : ({"/areas/street.c"}),
                 ]) );
    set_ghost_ok(0);
    
}
