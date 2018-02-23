inherit ROOM;

void create()
{
     set_light(1);
     set_short("A 'L' shaped hall way");
     set_long(
          "The long rows of bookcases continue on to the east\n"
          "and to the southwest is a study cubby. To the south\n"
          "east is another study cubby. A table with a stack of\n"
	   "books is here.\n"
              );
     set_exits( ([
          "north"  : "/areas/library/library15",
	   "east"   : "/areas/library/library18", 
	   "southeast" : "/areas/library/library20",
          "southwest"  : "/areas/library/library19",
     ]) );
     
}