inherit ROOM;

void create()
{
     set_light(1);
     set_short("The basement of the library");
     set_long(
          "This section of the library houses some of the more rare\n"
          "books. The musty smell here is almost overwhelming. The\n"
          "bookcases seem to be better built in this area however.\n"
        
              );
     set_exits( ([
          "southwest"  : "/areas/library/library16",
     ]) );
     
}