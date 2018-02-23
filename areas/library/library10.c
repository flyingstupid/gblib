inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the stacks of the library");
     set_long(
          "Bookshelves line the north and east walls of the library.\n"
          "The shelves allow you the move farther west or south into\n"
          "the stacks.There are stairs that lead into the basement.\n"
        
              );
     set_exits( ([
          "south": "/areas/library/library7",
          "west" : "/areas/library/library9",
          "down" : "/areas/library/library11",
     ]) );
     
}
