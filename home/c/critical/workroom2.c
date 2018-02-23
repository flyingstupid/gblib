/* workroom.c

*/



inherit ROOM;

void create()
{
     set_light(1);
     set_short("Criticalfault's Lair");
     set_long(
          "\tFour solid concrete walls with a bland white painted floor.\n"
          "Computers are stacked in each corner, running smoothly. The\n"
          "sound of whirling fans can be heard.\n"
     );
     set_exits( ([
          "cafe" : ({"/areas/lpuni/entrance.c"}),
          "void" : ({"/areas/std/void.c"}),
        "library": ({"/areas/library/library00.c"}),
        "academy": ({"/areas/academy/academy01.c"}),
        "morgue" : ({"/areas/morgue/morgue.c"}),

     ]) );
}