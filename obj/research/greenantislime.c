//
//  /obj/research/greenantislime.c
//  GB Mud
//


inherit "/obj/research/antislime.c";

/* FUNCTIO PROTOTYPES */
void pour_green_antislime();
void clear_Enhancement();



void create()
{
    ::create();
    
    set_id(({"anti-slime", "antislime", "green antislime", "green anti-slime"}));
    set_short("green anti-slime");
    set_long ("A vial full of a green viscous liquid that seems to undulate gently.");
    set_potency(1);
    set_enhancement("armor_green");
    
}


