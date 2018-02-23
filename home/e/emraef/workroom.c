inherit ROOM;

void create()
{
     set_light(1);
     set_short("Emraef's Lair");
     set_long( "The walls are a painted taupe (they say taupe is very soothing.)\n"
               "There is a painting of the creators of the mud Emraef and\n"
               "Critical on the north wall. The creators are depicted playing\n"
               "cards with a group of dogs. The room is lit by several candelabras\n"
               "along the walls.\n"
             );
     set_exits( ([
          "void" : "/areas/std/void.c"
     ]) );
     set_ghostExits( ([
          "locker" : ({ "/home/e/emraef/locker.c", " passes through the west wall.", " enters through the east wall." })
     ]) );
}
