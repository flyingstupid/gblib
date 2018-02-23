//
//  /obj/research/collectedslime.c
//  GB Mud
//


inherit "/obj/research/collectedSample.c";


void create()
{
    ::create();
    
    set_id(({"sample", "slime", "Slime", "Sample"}));
    set_short("vial of green slime");
    set_long ("A thick green ooze contained in a glass vial");
    set_research_time(12000);
    set_type("slime");
}


