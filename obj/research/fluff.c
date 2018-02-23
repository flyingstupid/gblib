/* slime.c - used to make slime for research*/
/*    /obj/research/fluff.c  */


inherit "/obj/research/sample.c";



void create()
{
    set_id(({"fluff"}));
    set_short("Fluff");
    set_long ("a bit of fluff");
    set_collect_diff (0);
    
    
    SetResearchValue(5);
    SetResearchTime(15);
    SetResearchChance(100);
    SetResearchQuality(1);
    SetResearchPrepared(0);
    SetWasFumbled(0);
    SetPrepTime(120);
    SetVessel("vial");
}





