/* slime.c - used to make slime for research*/


inherit "/obj/research/sample.c";


void create()
{
    set_id(({"sample", "slime", "Slimer", "Sample"}));
    set_short("some slime");
    set_long ("a puddle of slime");
    SetResearchValue(100);
    SetResearchTime(15);
    SetResearchChance(100);
    SetResearchQuality(1);
    SetResearchPrepared(0);
    SetWasFumbled(0);
    SetVessel("vial");
}





