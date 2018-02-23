inherit ROOM;
void create()
{
     set_light(1);
     set_short("Hallway");
     set_long("Insert Description here!");
     set_exits( ([
	 
          "north" : ({"/home/a/alice/lhome/lhome10.c", 1}),
		  "south" : ({"/home/a/alice/lhome/lhome6.c"}),
          "east" : ({ "/home/a/alice/lhome/lhome9.c", 1 }),
		  "up" : ({ "/home/a/alice/lhome/lhome12.c", 1 })
		  
     ]) );
}
