inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the stacks of the library");
     set_long(
          "Bookshelves line the south and west walls of the library.\n"
          "The shelves allow you the move farther north into the stacks\n"
          "or to the east into the checkout area.\n"
        
              );
     set_exits( ([
          "north" : ({"/areas/library/library5"}),
          "east" : ({"/areas/library/library3"}),
     ]) );
     
}
