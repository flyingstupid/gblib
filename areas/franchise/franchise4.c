inherit ROOM;
object unit;
void create()
{
     set_light(1);
     set_short("The Basement");
     set_long(
          "A bland room with wooden stairs. A containment unit is against\n the
wall.\n"

     );
     set_exits( ([
          "up" : "/areas/franchise/franchise1.c",

     ]) );
unit=clone_object("obj/containmentunit.c");
unit->move("/areas/franchise/franchise4.c");    
}

