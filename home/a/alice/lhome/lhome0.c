inherit ROOM;

void create()
{
     set_light(1);
     set_short("Porch");
     set_long("Insert Description here!");
     set_exits( ([
	 
          "door" : ({ "/home/a/alice/lhome/lhome1.c", 1 })
		  
     ]) );
	 
     set_items( ([
          "vase" : "The vase has a bouquet of dead flowers sitting in putrid\n"
          "water.\n"
     ]) );
}
