inherit ROOM;

void create()
{
     set_light(1);
     set_short("Emraef's Locker");
     set_long( "The walls are bare and are painted  bright white. A single\n"
               "light bulb hangs from a wire poking out of a crude hole cut\n"
               "in the ceiling. An ornate fountain sits just under the light.\n"
               "The fountain is filled with what is unmistakenly blood. Given\n"
               "where you are it can only be the blood of fallen players.\n"
             );
     set_ghostExits( ([
          "workroom" : ({ "/home/e/emraef/workroom.c", " passes through the east wall.", " enters through the west wall." })
     ]) );
}
