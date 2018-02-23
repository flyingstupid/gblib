inherit OBJECT;

int setupwall();
void finishsetupwall();
int activatewall();
int deactivatewall();
int breakdownwall();
void finishbreakdownwall();
int getlives();
void setlives( int num );
int getsetup();
void setsetup( int num );
int ison();
void seton( int num );
string querylong();

int on;
int lives;
int setup;
object room;

void create()
{
    set_id(({"ghostwall", "GhostWall", "wall", "Wall"}));
    set_short("ghostwall");
    set_long("A small device which can be setup (setupwall) to stop ghosts from entering\nafter you activate (activatewall) it. When you finish with it you can deactivate it (deactivatewall) and break it down (breakdownwall).");
	lives=3;
	setup=0;
	setValue(10000);
}

string query_long()
{
	
	return  "Activations Left: " + getlives() + "\n" + ::query_long();	
	
}

void init()
{
	add_action("setupwall","setupwall");
	add_action("activatewall","activatewall");
	add_action("deactivatewall","deactivatewall");
	add_action("breakdownwall","breakdownwall");
}

int setupwall()
{
	write("You begin to setup the ghost wall...\n");
	say(this_player()->query_cap_name() + " begins to setup a ghostwall.\n");
	call_out("finishsetupwall",10);
	setsetup(1);
	return 1;	
}


void finishsetupwall()
{
	
	room=environment(this_player());
	this_object()->move(room);
	this_object()->set("prevent_get", 1);
	write("You finish setting up the ghostwall.\n");
	say(this_player()->query_cap_name() + " finishes the setup on the ghostwall.\n");
	
}

int activatewall()
{
	if(setup==1 && !ison() )
	{
		seton(1);
		room->set_ghost_ok(0);
		write("You flip the switch on the ghost wall and it hums to life.\n");
		say(this_player()->query_cap_name() + " flips a switch on the ghost wall. It hums to life.\n");
		lives--;
		return 1;
	}
	else
	{
		write("The device is already on!\n");
		return 1;	
	}
}

int deactivatewall()
{
	
	if(setup==1 && ison() )
	{
		seton(0);
		room->set_ghost_ok(1);
		write("You flick the switch on the ghost wall and the humming stops.\n");
		say(this_player()->query_cap_name() + " flicks a switch on the ghostwall.\nIt stops humming.\n");
		if(lives==0)
		{
			destruct(this_object());
			say(this_player()->query_cap_name() + " diposes of the useless ghostwall.\n");	
			write("The battery is dead on the ghostwall, you dispose of it.\n");
		}
		return 1;	
	}
	else
	{
		write("The device isnt even on!\n");	
		return 1;
	}
}

int breakdownwall()
{
	write("You begin to breakdown the ghost wall.\n");
	say(this_player()->query_cap_name() + " begins to breakdown the ghostwall.\n");
	call_out("finishbreakdownwall",10);	
	return 1;	
}

void finishbreakdownwall()
{
	setsetup(0);
	write("You finish the break down and grab it.\n");
	say(this_player()->query_cap_name() + "finishes breaking down the ghostwall and then picks it up.\n");
	this_object()->set("prevent_get", 0);
	this_object()->move(this_player());	
}

int getsetup()
{
	return setup;
}

void setsetup( int num )
{
	setup=num;	
}

int getlives()
{
	return lives;	
}

void setlives( int num )
{
	lives=num;
}

int ison()
{
	return on;
}

void seton( int num )
{
	on=num;	
}
