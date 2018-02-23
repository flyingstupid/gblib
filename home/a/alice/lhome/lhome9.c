inherit ROOM;
void create()
{
     set_light(1);
     set_short("Bathroom");
     set_long("Insert Description here!");
     set_exits( ([
	 
          "west" : ({ "/home/a/alice/lhome/lhome8.c", 1 })
		  
     ]) );
}
