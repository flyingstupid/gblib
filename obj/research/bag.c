//
//  /obj/research/bag.c
//  GB mud
//

inherit "/obj/research/vessel.c";


void create()
{
    ::create();
    
    set_id(({"bag", "Bag", "Sample bag", "sample bag"}));
    set_short("sample bag");
    set_long ("a plastic bag with the word SAMPLE stamped across the front");
    SetFill(0);
    set_type("bag");
    
}
