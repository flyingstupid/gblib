inherit ROOM;

#define ROOM_LINE_SIZE 7

void create()
{
     set_light(1);
     set_short("NorthRoom");
     set_long( "This is the north room\n" );
     set_exits( ([
          "south"     : "/home/e/emraef/areas/vmap/roomCenter.c",
          "east"      : "/home/e/emraef/areas/vmap/roomNorthEast.c",
          "west"      : "/home/e/emraef/areas/vmap/roomNorthWest.c",
          "southwest" : "/home/e/emraef/areas/vmap/roomWest.c",
          "southeast" : "/home/e/emraef/areas/vmap/roomEast.c",
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'You are never given a wish without also being given the\n"
               "power to make it come true. You may, however, have to work for\n"
               "it.'\n",
     ]) );
}
