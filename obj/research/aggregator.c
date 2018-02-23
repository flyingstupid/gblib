//
//  /obj/research/aggregator.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"aggregator"}));
    set_short("serum aggregator");
    set_long ("a big thing with lots of vials and condensation tubes");
    set_cost (1750000);
    set_location("liquid");
    
}
