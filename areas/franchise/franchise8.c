inherit ROOM;

object biz;

void create()
{
     set_light(1);
     set_short("Ghostbuster Business Area");
     set_long(
          "This large office is home to the man with the money. Hes in the business of handing out money on behalf of the city for new busters jobs. Hes easy to get along with and happy to lend you an ear if you need some money. Just TALK to him and see what hes got on his plate. Once you've finished what you've given just FINISH you business with him here."
     );
     set_exits( ([
          "north" : ({"/areas/franchise/franchise3.c",2})
          
     ]) );
     


biz = clone_object("/areas/franchise/mobiles/bizagent.c");
biz->move("/areas/franchise/franchise8.c");
}
