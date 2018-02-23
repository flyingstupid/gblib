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
          "south"       : ({ "/areas/demo/demo3"}),
          "east"        : ({ "/areas/demo/demo5"}),
          "southeast"   : ({ "/areas/demo/demo2"}),
          "exitdemo"    : ({ "/areas/demo/demo1"})
     ]) );
}
