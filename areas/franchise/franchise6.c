inherit ROOM;

object trainer;

void create()
{
     set_light(1);
     set_short("The Training Room");
     set_long(
          "An arry of machines are setup here for any ghostbuster\n"
          "to try and work with.\n"
     );
     set_exits( ([
          "down" : "/areas/franchise/franchise1.c",
     ]) );
trainer=clone_object("/obj/train/dodgetrainer0.c");
trainer->move("/areas/franchise/franchise6.c");
}
