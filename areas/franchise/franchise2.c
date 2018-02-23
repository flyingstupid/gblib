inherit ROOM;

void create()
{
     set_light(1);
     set_short("Sleeping Quarters");
     set_long(
          "A drab room with a few beds and dressers. A large\n"
          "floor rug covers the rough looking and chipped wooden\n"
          "floor.\n"
     );
     set_exits( ([
          "east" : ({"/areas/franchise/franchise1.c", 0 }),
          "west" : ({"/areas/franchise/franchise7.c", 2 })

     ]) );
     
}
