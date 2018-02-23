//
//  /obj/research/collectedliquid.c
//  GB Mud
//


inherit "/obj/research/collectedSample.c";


void create()
{
    ::create();
    
    set_id(({"sample", "liquid", "Liquid", "Sample"}));
    set_short("tube of clear liquid");
    set_long ("A clear liquid contained in a glass vial");
    set_research_time(15000);
    set_type("liquid");
}
