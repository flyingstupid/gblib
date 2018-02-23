//
//  /obj/research/purpleantislime.c
//  GB Mud
//


inherit "/obj/research/antislime.c";

/* FUNCTIO PROTOTYPES */




void create()
{
    ::create();
    
    set_id(({"anti-slime", "antislime", "purple antislime", "Purple anti-slime"}));
    set_short("purple anti-slime");
    set_long ("A vial full of a viscous purple liquid that seems to undulate gently.");
    set_potency(1);
    set_enhancement("armor_purple");
    
}
