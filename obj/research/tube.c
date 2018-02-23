//
//  /obj/research/tube.c
//  GB mud
//


inherit "/obj/research/vessel.c";


void create()
{
    ::create();
    
    set_id(({"tube"}));
    set_short("test tube");
    set_long ("a glass test tube with a rubber stopper");
    SetFill(0);
    set_type("tube");
    
}
