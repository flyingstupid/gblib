//
//  /obj/research/orangeantislime.c
//  GB Mud
//


inherit "/obj/research/antislime.c";

/* FUNCTIO PROTOTYPES */




void create()
{
    ::create();
    
    set_id(({"anti-slime", "antislime", "orange antislime", "orange anti-slime"}));
    set_short("orange anti-slime");
    set_long ("A vial full of an orange viscous liquid that seems to undulate gently.");
    set_potency(1);
    set_enhancement("armor_orange");
    
}
