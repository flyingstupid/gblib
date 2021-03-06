//
//  GBMUD
//  /areas/labyrinth/green6.c
//

inherit "/areas/labyrinth/green_base.c";


void create()
{
    ::create();   
    set_long(
             "The walls of this room are made of lovely bushes with large\n"
             "pink flowers.  In the distance you can hear birds singing and\n"
             "the air is fresh and pure.\n"
             );
    set_exits( ([
                 "north" : ({ "/areas/labyrinth/green7"}),
                 "south" : ({ "/areas/labyrinth/green5"}),
                 ]) );
}