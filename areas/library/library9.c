inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the stacks of the library");
     set_long(
          "Bookshelves line the north walls of the library. The shelves\n"
          "allow you the move farther west or south into the stacks.\n"
          "To the south is the study area.\n"
        
              );
     set_exits( ([
          "south": "/areas/library/library6",
          "east" : "/areas/library/library10",
          "west" : "/areas/library/library8",
     ]) );
     
}
