//
//  /obj/research/fabricator.c
//

inherit "/obj/research/equipment.c";

void create()
{
    ::create();
    
    set_id(({"fabricator", "Fabricator", "Fabricating machine", "machine", "Machine", "fabricating machine"}));
    set_short("fabricating machine");
    set_long ("A large metal machine with three blinking buttons one the top.");
    set_cost(300000);
    set_location("lab");
}
