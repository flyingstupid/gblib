inherit OBJECT;

void create()
{
    set_id(({"pill", "med",}));
    set_short("small white pill");
    set_long("A small white pill with 'calm' carved into it. You can MEDICATE with it.");   
}

void init()
{
	add_action("medicate","medicate");
}


int medicate()
{	
	if(this_player()->CheckForStatus("shaken"))
	{
		write("You swallow the pill and try to relax...");
		call_out("finish()",5);
		destruct(this_object());
	}
	else
	{
		write("You don't need to be medicated!\n");
	}
	return 1;
}

void finish()
{
	write("After awhile you calm down.\n");
	this_player()->ClearStatus("shaken");	
}
