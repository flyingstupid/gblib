//
// liquid.c - used to make liquids for research
//    /obj/research/liquid.c
//


inherit "/obj/research/sample.c";



void create()
{
    ::create();
    
    set_id(({"sample", "liquid", "Liquid", "Sample"}));
    set_short("a clear liquid");
    set_long ("a pool of clear liquid");
    set_collect_diff(30);
    set_base_value(120);
    set_type("liquid");
    set_examine_time(15000);
    set_vessel("tube");
}
