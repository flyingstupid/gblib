inherit ROOM;
void create()
{
     set_light(1);
     set_short("Kitchen");
     set_long("Insert Description here!");
     set_exits( ([
	 
	      "north" : ({ "/home/a/alice/lhome/lhome3.c"}),
          "east" : ({ "/home/a/alice/lhome/lhome2.c", 1 }),
          "down" : ({ "/home/a/alice/lhome/lhome11.c", 1 }),
          "out" : ({ "/home/a/alice/lhome/lhome0.c", 1 })

     ]) );
     set_items( ([
          "vase" : "The vase has a bouquet of dead flowers sitting in putrid\n"
          "water.\n"
     ]) );
}
