inherit ROOM;
void create()
{
     set_light(1);
     set_short("Bedroom");
     set_long("Insert Description here!");
     set_exits( ([
	 
          "west" : ({ "/home/a/alice/lhome/lhome3.c", 1 })
		  
     ])  );
     set_items( ([
          "portraits" : "The portraits of the family are hung on the wall. The
eyes\n"
          "of the little girl seem to follow you as you look at her.\n"
          "Or maybe it was a trick of the light...?\n"
     ]) );
}
