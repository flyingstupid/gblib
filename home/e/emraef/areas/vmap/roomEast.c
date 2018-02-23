inherit ROOM;

#define ROOM_LINE_SIZE 7

void create()
{
     set_light(1);
     set_short("EastRoom");
     set_long( "This is the east room\n" );
     set_exits( ([
          "north"     : "/home/e/emraef/areas/vmap/roomNorthEast.c",
          "south"     : "/home/e/emraef/areas/vmap/roomSouthEast.c",
          "west"      : "/home/e/emraef/areas/vmap/roomCenter.c",
          "northwest" : "/home/e/emraef/areas/vmap/roomNorth.c",
          "southwest" : "/home/e/emraef/areas/vmap/roomSouth.c",
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'You are never given a wish without also being given the\n"
               "power to make it come true. You may, however, have to work for\n"
               "it.'\n",
     ]) );
}
