inherit ROOM;
void create()
{
     set_light(1);
     set_short("Dining room");
     set_long("Insert Description here!");
     set_exits( ([
	 
         "west" : ({ "/home/a/alice/lhome/lhome1.c", 1 })
		 
     ]) );
}
