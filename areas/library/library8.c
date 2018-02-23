inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the stacks of the library");
     set_long(
          "Bookshelves line the north and west walls of the library.\n"
          "The shelves allow you the move farther east or south into\n"
          "the stacks.\n"
        
              );
     set_exits( ([
          "south": "/areas/library/library5",
          "east" : "/areas/library/library9",
     ]) );
     
}
