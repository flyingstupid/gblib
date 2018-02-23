inherit ROOM;

#define ROOM_LINE_SIZE 7

void create()
{
     set_light(1);
     set_short("CenterRoom");
     set_long( "This is the center room\n" );
     set_exits( ([
          "north"     : "/home/e/emraef/areas/vmap/roomNorth.c",
          "south"     : "/home/e/emraef/areas/vmap/roomSouth.c",
          "east"      : "/home/e/emraef/areas/vmap/roomEast.c",
          "west"      : "/home/e/emraef/areas/vmap/roomWest.c",
          "northwest" : "/home/e/emraef/areas/vmap/roomNorthWest.c",
          "northeast" : "/home/e/emraef/areas/vmap/roomNorthEast.c",
          "southwest" : "/home/e/emraef/areas/vmap/roomSouthWest.c",
          "southeast" : "/home/e/emraef/areas/vmap/roomSouthEast.c",
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'You are never given a wish without also being given the\n"
               "power to make it come true. You may, however, have to work for\n"
               "it.'\n",
     ]) );
}
