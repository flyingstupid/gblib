//
//  /obj/research/enhancer.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"enhancer"}));
    set_short("Weapon Ehnahcer");
    set_long ("a bench with a vice and sevarl small tools scattered ove the top");
    set_cost (2000000);
    set_location("artifact");
    
}
