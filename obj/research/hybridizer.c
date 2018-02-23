//
//  /obj/research/hybridizer.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"hybridizer"}));
    set_short("Anti-slime Hybridizer");
    set_long ("A large stainless steel machine with lots of tubes and slots");
    set_cost (1250000);
    set_location("slime");
    
}
