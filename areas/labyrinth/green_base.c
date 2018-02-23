//
//  GBMUD
//  /areas/labyrinth/green_base.c
//
inherit ROOM;

#define VERMIN  "/obj/npcs/ghosts/squirrel.c"
#define HERE   "/areas/labyrinth/green1.c"

int ghostChance;
object ob;

void create()
{
    ::create();
    
    set_light(1);
    set_short("Labyrinth");
    set_long(
             "The walls of this room are made of lovely bushes with large\n"
             "pink flowers.  In the distance you can hear birds singing and\n"
             "the air is fresh and pure.\n"
             );
    set_exits( ([
                 "east" : ({ "/areas/labyrinth/entry"}),
                 "west" : ({ "/areas/labyrinth/green2"}),
                 ]) );
    set_ghost_ok(0);
    
    ghostChance = random (8);
    ob = clone_object( VERMIN );
    if (ghostChance == 5)
    {
        load_object( VERMIN );
        ob->move( this_object() );
    }
    set_heart_beat(120);
    
}

void heart_beat(){
    tell_room(this_object(), "Checking for vermin\n");
    if (!present ("squirrel", this_object()))
    {
        
        ghostChance = random (8);
        tell_room (this_object(), "There are no ghosts, using number " + ghostChance + "to create a new one.\n");
        if (ghostChance == 5)
        {
            ob = clone_object( VERMIN );
            load_object( VERMIN );
            ob->move( this_object() );
        }
        
    }
}