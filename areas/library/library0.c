inherit ROOM;

void create()
{
     set_light(1);
     set_short("The Front of the library");
     set_long(
          "Massive multilevel steps lead up to a red bricked\n"
          "building. Its old style look leads to the old fashion\n"
          "feeling the building has tried so hard to maintain.\n"
          "A sign is bolted to the front of the door.\n"
     );
     set_exits( ([
          "north" : ({ "/areas/library/library1", 2,
"/areas/library/mainentrancekey.c" }),
"street" : ({"/areas/street.c"}),
     ]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "'New York Public Library\n",
     ]) );
}
