inherit ROOM;

void create()
{
     set_light(1);
     set_short("Items and how they work!");
     set_long(
          "Our game contains many objects. Each object has a special function. From keys\n"
          "that unlock doors to protonpacks that let you contain ghosts. LOOK at the SIGN\n"
          "to get more information. There is a ball in the room you can GET when you are\n"
          "ready to move on.\n"
); 
     set_exits( ([
           "south" : "/areas/academy/academy2.c",
           "north" : "/areas/academy/academy4.c",

]) );
     set_items( ([
          "sign" : "The commands we will go over are. GET, DROP, INVENTORY, WEAR, REMOVE, EQUIPMENT\n\n"
                   "%^GREEN%^GET%^RESET%^: This command will grab an item and put it into your inventory. In your\n"
                   "inventory if the item has a special ability. More than likely you'll need\n"
                   "to have it worn to useit. Some special objects you need to just be in the\n"
                   "room to use.\n\n"
                   "%^GREEN%^DROP%^RESET%^:If you need to get something out of your inventory, simply\n"
                   "drop it. This takes an item from your inventory and drops it on the ground. So\n"
                   "if you want to keep an item. Don't drop it. drop <item>\n\n"
                   "%^GREEN%^INVENTORY%^RESET%^: This command will show everything that is in your inventory. You\n"
                   "can also just type i\n\n"
                   "%^GREEN%^WEAR%^RESET%^: Some objects require you to wear them before they can be used correctly.\n"
                   "Armor, Protonpacks, glasses, etc need to be worn before their benefit will be given.\n\n"
                   "%^GREEN%^REMOVE%^RESET%^: this is the opposite of wear. It takes an item off of your wear list\n"
                   "and puts it back into your inventory.\n\n"
                   "%^GREEN%^EQUIPMENT%^RESET%^: This command will show you what your character is wearing. Its sort is EQ\n"

]) );
}
