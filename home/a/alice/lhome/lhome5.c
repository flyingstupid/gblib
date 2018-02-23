inherit ROOM;
void create()
{
     set_light(1);
     set_short("Living room");
     set_long("Insert Description here!");
     set_exits( ([
	 
	      "south" : ({ "/home/a/alice/lhome/lhome3.c"})
		  
     ]) );
}
