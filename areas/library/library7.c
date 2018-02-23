inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the stacks of the library");
     set_long(
          "Bookshelves line the east walls of the library. The shelves\n"
          "allow you the move farther north into the stacks or to the\n"
          "or to the west. Which is the study area.\n"
        
              );
     set_exits( ([
          "north" : "/areas/library/library10",
          "south" : "/areas/library/library4",
          "west"  : "/areas/library/library6",
     ]) );
     
}
