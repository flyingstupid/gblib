inherit ROOM;
void create()
{
     set_light(1);
     set_short("Bedroom");
     set_long("Insert Description here!");
     set_exits( ([
	 
          "west" : ({"/home/a/alice/lhome/lhome6.c", 1 })
		  
     ]) );
}
