//
//  /obj/research/infuser.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"infuser"}));
    set_short("Anti-slime infuser");
    set_long ("a very large pressing machine with a space for a vila of slime");
    set_cost (6000000);
    set_location("slime");
    
}
