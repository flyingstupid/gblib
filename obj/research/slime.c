/* slime.c - used to make slime for research*/
/*    /obj/research/slime.c  */


inherit "/obj/research/sample.c";



void create()
{
    ::create();
    
    set_id(({"sample", "slime", "Slimer", "Sample"}));
    set_short("Green slime");
    set_long ("a puddle of slime");
    set_collect_diff(20);
    set_base_value(100);
    set_type("slime");
    set_examine_time(12000);
    set_vessel("vial");
}





