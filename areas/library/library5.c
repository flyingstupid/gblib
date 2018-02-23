inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the stacks of the library");
     set_long(
          "Bookshelves line the west walls of the library. The shelves\n"
          "allow you the move farther north into the stacks or to the\n"
          "or to the east. Which is the study area.\n"
        
              );
     set_exits( ([
          "north" : ({"/areas/library/library8"}),
          "south" : ({"/areas/library/library2"}),
          "east"  : ({"/areas/library/library6"}),
     ]) );
     
}
