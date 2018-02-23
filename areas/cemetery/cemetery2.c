/*
Cemetery Area!
-Constructed by Critical
-Described and filled by Alice!

*/

inherit ROOM;

void create()
{
	set_light(1);
	set_short("Church Cemetery");
	set_long("Insert Description here!");
	set_exits( ([
	
	"west" : ({"areas/cemetery/cemetery1.c"}),
	"east" : ({"areas/cemetery/cemetery3.c"}),
	"south": ({"areas/cemetery/cemetery6.c"}),
	"exit" : ({"areas/street.c"})
	
	
	]));
}
