inherit ROOM;

void create()
{
     set_light(1);
     set_short("Laboratory");
     set_long(
          "A large room with various medical and science related\n"
          "items adoring the walls.\n"
     );
     set_exits( ([
          "south": "/areas/franchise/franchise1.c",
     ]) );
     
}
