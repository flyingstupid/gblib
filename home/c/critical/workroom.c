/* workroom.c

*/



inherit ROOM;

void create()
{
     set_light(1);
     set_short("Criticalfault's Lair");
     set_long(
          "\tFour solid concrete walls with a bland white painted floor. Computers are stacked in each corner, running smoothly. The sound of whirling fans can be heard."
     );
     set_exits( ([
          
          "void" : ({"/areas/std/void.c"}),
        "library": ({"/areas/library/library1.c"}),
        "morgue" : ({"/areas/morgue/morgue.c"}),
		"street" : ({"areas/street.c"})

     ]) );
}