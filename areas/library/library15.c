inherit ROOM;

void create()
{
     set_light(1);
     set_short("The basement of the library ");
     set_long(
          "The long rows of bookcases continue on to the south\n"
          "and the lighting in this row seems a bit better. There\n"
          "is a small bookcart with a radio on it, playing soft music.\n"
              );
     set_exits( ([
          "north"  : "/areas/library/library12",
          "south"  : "/areas/library/library17",
     ]) );
     
}