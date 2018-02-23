inherit ROOM;
void create()
{
     set_light(1);
     set_short("Hallway");
     set_long("Insert Description here!");
     set_exits( ([
	 
          "north" : ({ "/home/a/alice/lhome/lhome8.c", 1 }),
		  "down" : ({"/home/a/alice/lhome/lhome3.c"}),
          "east" : ({ "/home/a/alice/lhome/lhome7.c", 1 })
		  
     ]) );
}
