inherit ROOM;

void create()
{
     set_light(1);
     set_short("Street Junction");
     set_long(
          "The streets are filled with various locations you can find! For now we've simplified it to a single room with lots of exits. A much better one will be made another time!"
     );
     set_exits( ([
          "library" : ({"/areas/library/library0.c"}),
          "er"		: ({"/areas/hospital/hospitalER.c"}),
          "franchise":({"/areas/franchise/franchise.c"}),
          "demo"    : ({"/areas/demo/demo1.c"}),
		  "cemetery": ({"/areas/cemetery/cemetery2.c"}),
          "labyrinth": ({"/areas/labyrinth/entry.c"})        
                  
     ]) );

}
