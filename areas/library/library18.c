inherit ROOM;

void create()
{
     set_light(1);
     set_short("The basement of the library ");
     set_long(
          "Holder for the room desc \n",
              );
     set_exits( ([
          "north"  : "/areas/library/library16",
          "west"  : "/areas/library/library17",
     ]) );
     
}