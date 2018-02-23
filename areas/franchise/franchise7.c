inherit ROOM;

object shower;

void create()
{
     set_light(1);
     set_short("Locker Room");
     set_long(
          "A large room covered in white tiles. Sinks and showers\n"
          "line the walls sperated by half walls. Toilets in stalls\n"
          "for privacy and lockers line the walls for personal affects.\n"
          "Soft white lights are shielded from the spray and lots of \n"
          "shelves with toiletries.\n"
     );
     set_exits( ([
          "east" : ({"/areas/franchise/franchise2.c",2,})

     ]) );

shower=clone_object("/obj/shower.c");
shower->move("/areas/franchise/franchise7.c");
}

