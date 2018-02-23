//
//  /obj/research/goldantislime.c
//  GB Mud
//


inherit "/obj/research/antislime.c";

/* FUNCTIO PROTOTYPES */




void create()
{
    ::create();
    
    set_id(({"anti-slime", "antislime", "gold antislime", "Gold anti-slime"}));
    set_short("gold anti-slime");
    set_long ("vial full of a viscous gold liquid that seems to undulate gently.");
    set_potency(1);
    set_enhancement("armor_gold");
    
}
