inherit ROOM;
void create()
{
     set_light(1);
     set_short("Hallway");
     set_long("Insert Description here!");
     set_exits( ([
	 
	      "north" : ({ "/home/a/alice/lhome/lhome5.c"}),
          "east" : ({ "/home/a/alice/lhome/lhome4.c", 1 }),
		  "south" : ({ "/home/a/alice/lhome/lhome1.c"}),
		  "up" : ({ "/home/a/alice/lhome/lhome6.c"})
		  
	 ]) );
}
