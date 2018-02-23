inherit ROOM;
void create()
{
     set_light(1);
     set_short("Bathroom");
     set_long("Insert Description here!");
     set_exits( ([
	 
		  "south" : ({"/home/a/alice/lhome/lhome6.c", 1 })
		  
     ]) );
}
