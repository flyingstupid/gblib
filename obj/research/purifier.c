//
//  /obj/research/purifier.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"purifier"}));
    set_short("liquid purifier");
    set_long ("A glass and plastic machine with a narrow funnel at the top");
    set_cost (550000);
    set_location("liquid");
    
}
