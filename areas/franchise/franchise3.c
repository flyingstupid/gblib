inherit ROOM;

object shopkeeper;
object pack;
object meter;
object trap;
object ghostwall; 
object grenade;

void create()
{
     
     set_light(1);
     set_short("The Franchise Store");
     set_long(
          "This room is the only one that doesn't look tarnished\n"
          "or decayed. A long polished counter runs the length of\n"
          "this room. A metal cage is firmly attatched to the wall\n"
          "and is kept under lock in key. The cage is full of new gear.\n"
     );
     set_exits( ([
          "west" : "/areas/franchise/franchise1.c",
          "south" : ({"/areas/franchise/franchise8.c", 2 })
     ]) );
//create and then place the shopkeeper!
shopkeeper=clone_object("/areas/franchise/mobiles/shopkeeper.c");
shopkeeper->move("/areas/franchise/franchise3.c");

//Franchise ShopKeeper's Inventory for sale!
pack=clone_object("/obj/protonpack/protonpack.c");
meter=clone_object("/obj/pkemeter/pkemeter.c");
trap=clone_object("/obj/trap/trap.c");
ghostwall=clone_object("/obj/gadgets/ghostwall.c");
grenade=clone_object("/obj/gadgets/pkegrenade.c");

//Move them to him!
pack->move(shopkeeper);
meter->move(shopkeeper);
trap->move(shopkeeper);
ghostwall->move(shopkeeper);
grenade->move(shopkeeper);
}
