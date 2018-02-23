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
          "north"       : ({ "/areas/demo/demo4"}),
          "east"        : ({ "/areas/demo/demo2"}),
          "northeast"   : ({ "/areas/demo/demo5"}),
          "exitdemo"    : ({ "/areas/demo/demo1"})
     ]) );
}
