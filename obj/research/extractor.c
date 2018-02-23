//
//  /obj/research/extractor.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"extractor"}));
    set_short("Slime Extractor");
    set_long ("A large stainless steel machine with lots of tubes and slots");
    set_cost (400000);
    set_location("slime");
    
}
