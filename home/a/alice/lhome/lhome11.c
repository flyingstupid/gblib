inherit ROOM;
void create()
{
     set_light(1);
     set_short("Basement");
     set_long("Insert Description here!");
     set_exits( ([
	 
		  "up" : ({"/home/a/alice/lhome/lhome1.c", 1 })
		  
     ]) );
}
