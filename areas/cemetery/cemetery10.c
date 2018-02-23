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
	
	"north" : ({"areas/cemetery/cemetery6.c"}),
	"east"  : ({"areas/cemetery/cemetery11.c"}),
	"west" : ({"areas/cemetery/cemetery9.c"})
	
	
	]));
}
	
