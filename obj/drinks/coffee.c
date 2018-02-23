// 
//     /obj/drink.c 
//     For all your beverage needs.
//     GB Mud
//


inherit "/obj/drink.c";


void create()
{
    set_id(({"mug", "coffee"}));
    set_short("mug of steaming coffee.");
    set_long("An plain white mug of steaming coffee.");
    is_drink();
    set_selfDrinkMsg("You take a sip from your delicious coffee.");
    set_roomDrinkMsg(" takes a drink of their coffee.");
    set_fill(10);
    
}
