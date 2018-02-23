inherit OBJECT;

void create()
{
    set_id(({"towel"}));
    set_short("towel");
    set_long("A large white fluffly towel. You could [WIPE] slime off you with this!");
   
}

void init()
{

	add_action("wipe","wipe");

}


int wipe()
{
	
	if(this_player()->CheckForStatus("slimed"))
	{
		write("You begin to towel the slime off yourself..\n");
       // tell_room(environment(this_player()),
		call_out("finish",5);
		
	}
	else
	{
		write("You don't need a towel!\n");
	}
	return 1;



}

void finish()
{
	write("You finish and are free of slime.\nThe towel is ruined, you dispose of it.\n");
    //te
	this_player()->ClearStatus("slimed");
    destruct(this_object());	
}
