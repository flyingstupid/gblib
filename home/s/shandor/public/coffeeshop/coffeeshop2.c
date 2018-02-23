inherit ROOM;
void create()
{
     set_light(1);
     set_short("A Coffeeshop");
     set_long(
          "The coffeeshop is a cookie-cutter of all the other coffeeshops\n"
          "in America. The smell of coffee lingers in the air. Several paper\n"
          "coffee cups sit on the tables.Several of chairs are knocked over.\n"
     );
     set_exits( ([
          "east" : "/home/s/shandor/public/coffeeshop/coffeeshop1.c"
     ]) );
}
