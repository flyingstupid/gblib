inherit ROOM;

void create()
{
     set_light(1);
     set_short("Ghostbuster Shopfront");
     set_long(
          "This store front has a short counter and limited\n"
          "seating. The floor has surely seen better days and\n"
          "the lights are a little dim. The walls are in desperate\n"
          "need of painting.\n"
     );
     set_exits( ([
          "north" : "/areas/franchise/franchise1",
          "street": "/areas/street.c",
     ]) );
     set_items( ([
          "sign" : "Standard charges:\n"
               "Proton Charging: $1000\n Entrapment:$2000\n",
     ]) );
}
