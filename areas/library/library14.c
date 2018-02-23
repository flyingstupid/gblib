inherit ROOM;

void create()
{
     set_light(1);
     set_short("The basement of the library - Study Area");
     set_long(
          "A small area between the bookshelves that has a table\n"
          "and a few chairs. Books are stacked all over the area\n"
          "waiting to be put away by the librarians\n"
              );
     set_exits( ([
          "east"  : "/areas/library/library15",
     ]) );
     
}