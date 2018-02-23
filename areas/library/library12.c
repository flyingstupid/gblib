inherit ROOM;

void create()
{
     set_light(1);
     set_short("The basement of the library");
     set_long(
          "The dim lights play off the shelves giving each book a\n"
          "sinister look. Card catalogs line the shelves of the east\n"
          "walls. To the south more bookshelves carry on for what seems\n"
          "like miles.\n"
        
              );
     set_exits( ([
          "west"  : "/areas/library/library11",
          "south" : "/areas/library/library15",
     ]) );
     
}
