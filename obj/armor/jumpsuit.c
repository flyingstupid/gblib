


//
//  Basic Jumpsuit
// /obj/armor/jumpsuit.c
//

inherit "/obj/armor.c";

void create()
{
        ::create();
    set_id(({"Jumpsuit", "jumpsuit"}));
    set_short("basic jumpsuit");
    set_long ("a standard issue Ghost busters jumpsuit.");
    set_base_defense (10);
    allowedWearLocs = ({"uniform"});
}
