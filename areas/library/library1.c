inherit ROOM;

void create()
{
     set_light(1);
     set_short("Inside the library");
     set_long(
          "Inside the library is a excellently carved marble floor\n"
          "with NYPL styled into the floor. Security devices line the\n"
          "front of the walkways so all partons must pass through them\n"
          "in order to get into the main area. Just a bit north is the\n"
          "counters for where books can be checked out and returned.\n"
     );
     set_exits( ([
          "north" : ({"/areas/library/library3"}),
          "south" : ({"/areas/library/library0", 2, ""}),
     ]) );
     
}
