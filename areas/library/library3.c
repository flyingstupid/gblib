inherit ROOM;

void create()
{
     set_light(1);
     set_short("Check-out area");
     set_long(
          "Long counters made of presswood fill this area to provide\n"
          "space for patrons to lay their finds out and be checked out\n"
          "by the librarians. To the east and the west it leads into the\n"
          "stacks.\n"
              );
     set_exits( ([
          "east" : ({"/areas/library/library4"}),
          "west" : ({"/areas/library/library2"}),
          "south": ({"/areas/library/library1"}),
     ]) );
     
}
