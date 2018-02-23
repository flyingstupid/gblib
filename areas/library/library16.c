inherit ROOM;

void create()
{
     set_light(1);
     set_short("The basement of the library ");
     set_long(
          "Holder for the room desc \n",
              );
     set_exits( ([
          "northeast"  : "/areas/library/library13",
          "south"  : "/areas/library/library18",
     ]) );
     
}