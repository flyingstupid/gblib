inherit OBJECT;


int toss();
void bang();

object tosser;
int primenumber;

void create()
{
	::create();
    set_id(({"grenade", "Grenade", "PKEGrenade", "pkegrenade"}));
    set_short("PKE grenade");
    set_long("A small cylindical device with a wired on LED display with a large red button. You may [TOSS] it when you need\n");
	setValue(25000);
}

void init()
{
	add_action("toss","toss");	
}

int toss()
{
	tosser=this_player();

	
	this_object()->move(environment(this_player()));
	this_object()->set("prevent_get",1);
	
	write("You toss the PKE Grenade onto the ground.\n");
	tell_room(environment(this_player()), this_player()->query_cap_name() + " tosses a PKE Grenade onto the ground!\n");
	call_out("bang",5);
	
	return 1;
}

void bang()
{

	object *targets;
    targets=all_inventory(environment(this_object()));
    write("The PKE Grenade explodes in a flash of PKE energy!\n");    
	tell_room(environment(this_object()),"The PKE Grenade explodes in a flash of PKE energy!\n");
    //tell_object(tosser,"[FINE]: $100 - Your grenade explodes!\n");
    for(int i=0; i < sizeof(targets); i++)
    {
	 	if(targets[i]->IsGhost())
	 	{
		 	
		 	
		 		targets[i]->SetStun(targets[i]->GetStun()+3);
			 	tell_room(environment(this_player()), targets[i]->query_cap_name() +" reels from the grenade's detonation!\n");
				write(targets[i]->query_cap_name() +" reels from the grenade's detonation!\n");
	 	}   
    }
    destruct();	
	
}

