inherit ROOM;
void create()
{
     set_light(1);
     set_short("A Coffeeshop");
     set_long(
          "The coffeeshop is a cookie-cutter of all the other coffeeshops\n"
          "in America. The smell of coffee lingers in the air. Several paper\n"
          "coffee cups sit on the tables.\n"
     );
     set_exits( ([
          "west" : "/home/s/shandor/public/coffeeshop/coffeeshop2.c"
     ]) );
}
