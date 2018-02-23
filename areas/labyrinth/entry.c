//
//  GBMUD
//  /areas/labyrinth/entry.c
//
inherit ROOM;

void equip();


object groundskeeper;

void create()
{
    set_light(1);
    set_short("Entry");
    set_long(
             "This is a small room with three exits into the labyrinth.  The\n"
             "walls are made of a smooth stone coverd in ivy with a few pink\n"
             "blossoms.  There is a sign on the wall and an old man stands\n"
             "in the corner.\n"
             );
    
    set_exits( ([
                 "north" : ({ "/areas/labyrinth/entry"}),
                 "east" : ({ "/areas/labyrinth/entry"}),
                 "west" : ({ "/areas/labyrinth/green1"}),
                 ]) );
    set_items( ([
                 "sign" : "A old and tattered sign is posted on the wall.  It looks like there may be something written on it.\n",
                 "sign" : "A old and tattered sign is posted on the wall.  It looks like there may be something written on it.\n"
                 ]) );    

    set_ghost_ok(0);
    
    //create and then place the shopkeeper!
    groundskeeper=clone_object("/areas/labyrinth/groundskeeper.c");
    groundskeeper->move("/areas/labyrinth/entry.c");
}
void init(){
    
    add_action ("equip", "equip");
    
}


/*-----------------------------------------------------------------------
 --------------------------  EQUIP FUNCTIONS  ---------------------------
 ------------------------------------------------------------------------*/

void equip(){
    object trap;
    object pack;
    
    trap = clone_object("/obj/trap/VerminTrap.c");
    trap->move(this_player());
    
    pack = clone_object("/obj/protonpack/protonpack.c");
    pack->move(this_player());
    
    return;
}