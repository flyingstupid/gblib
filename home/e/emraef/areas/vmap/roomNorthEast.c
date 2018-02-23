inherit ROOM;

#define ROOM_LINE_SIZE 7

void create()
{
     set_light(1);
     set_short("NorthEastRoom");
     set_long( "This is the north east room\n" );
     set_exits( ([
          "south"     : "/home/e/emraef/areas/vmap/roomEast.c",
          "west"      : "/home/e/emraef/areas/vmap/roomNorth.c",
          "southwest" : "/home/e/emraef/areas/vmap/roomCenter.c",
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'You are never given a wish without also being given the\n"
               "power to make it come true. You may, however, have to work for\n"
               "it.'\n",
     ]) );
}
