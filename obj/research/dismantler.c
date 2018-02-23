//
//  /obj/research/dismantler.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"dismantler", "Dismantler", "Dismantling machine", "dismantling machine"}));
    set_short("Dismatntling machine");
    set_long ("An enormous grantie block with a large hammer attached by a chain");
    set_cost (950000);
    set_location("artifact");
    
}
