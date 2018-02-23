inherit ROOM;

void create()
{
     set_light(1);
     set_short("The study area");
     set_long(
          "A few tables and cubbies are well spaced in this area\n"
          "to allow people to read or study in peace of other \n"
          "patrons. Its a pretty open area with a coffee maker\n"
          "and coffee supplies on a small table against the north\n"
          "wall.\n"
              );
     set_exits( ([
          "north" : ({"/areas/library/library9",}),
          "east"  : ({"/areas/library/library7",}),
          "west"  : ({"/areas/library/library5",})
     ]) );
     
}
