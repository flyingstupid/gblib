inherit ROOM;

#define ROOM_LINE_SIZE 7

void create()
{
     set_light(1);
     set_short("WestRoom");
     set_long( "This is the west room\n" );
     set_exits( ([
          "north"     : "/home/e/emraef/areas/vmap/roomNorthWest.c",
          "south"     : "/home/e/emraef/areas/vmap/roomSouthWest.c",
          "east"      : "/home/e/emraef/areas/vmap/roomCenter.c",
          "northeast" : "/home/e/emraef/areas/vmap/roomNorth.c",
          "southeast" : "/home/e/emraef/areas/vmap/roomSouth.c",
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'You are never given a wish without also being given the\n"
               "power to make it come true. You may, however, have to work for\n"
               "it.'\n",
     ]) );
}
