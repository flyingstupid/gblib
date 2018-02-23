inherit ROOM;

void create()
{
     set_light(1);
     set_short("The stairs in the library");
     set_long(
          "Stairs leading down to the basement where the older books\n"
          "are kept.The air is musty and the smell of decaying tomes\n"
          "is near overpowering. The stacks allow you to continue on\n"
          "to the east.\n"
        
              );
     set_exits( ([
          "east": "/areas/library/library12",
          "up"  : "/areas/library/library10",
     ]) );
     
}
