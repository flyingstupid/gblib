inherit ROOM;

#define ROOM_LINE_SIZE 7

void create()
{
     set_light(1);
     set_short("SouthWestRoom");
     set_long( "This is the south west room\n" );
     set_exits( ([
          "north"     : "/home/e/emraef/areas/vmap/roomWest.c",
          "east"      : "/home/e/emraef/areas/vmap/roomSouth.c",
          "northeast" : "/home/e/emraef/areas/vmap/roomCenter.c",
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'You are never given a wish without also being given the\n"
               "power to make it come true. You may, however, have to work for\n"
               "it.'\n",
     ]) );
}
