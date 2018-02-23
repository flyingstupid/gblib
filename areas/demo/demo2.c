inherit ROOM;

void create()
{
     set_light(1);
     set_short("Arena Room");
     set_long(
          "This is the Arena!\n"
          "Watch for them! They are everywhere!\n"
     );
     set_exits( ([
          "north"       : ({ "/areas/demo/demo5"}),
          "west"        : ({ "/areas/demo/demo3"}),
          "northwest"   : ({ "/areas/demo/demo4"}),
          "exitdemo"    : ({ "/areas/demo/demo1"})
     ]) );
}
