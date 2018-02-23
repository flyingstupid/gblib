inherit NPC;


void setup()
{
    set_living_name("ER doctor");
    set_name("ER doctor");
    set_short("An ER doctor stands behind the desk");
    set_long("He is an average ER doctor.\n");

    set_id( ({"doc", "doctor", "er doctor"}) );
}

void enter_env()
{
     tell_room( environment(this_object()),"The ER doctor looks you over.\n
	      The ER doctor says, 'Do you need assistance? I can HEAL you up.'\n" );
}
