//
//  /areas/franchise/mobiles/bizagent.c
//  GB Mud
//

inherit NPC;

int talk();
int finish();
void FindJob();
void greet();


void setup()
{
    set_living_name("bizagent");
    set_name("Business Agent");
    set_short("The Business Agent");
    set_long("Hes the business agent of the ghostbusters local franchise.\n");
    set_id( ({"business", "agent", "Business", "Agent",}) );
    setReplies( ([
                  "job" : "I work here helping new busters find work and paying them for it.",
                  "name": "My name is John",
                  "pay" : "I pay between 200-300 dollars per ghost returned to me. Enough for a new trap and some extra",
                  "work" : "If you want to work, lets TALK.",
                  "done" : "Alright, lets FINISH this then.",
                  "finish": "Just FINISH it already!",
                  ])  );
}

void init()
{
	call_out("greet",1);	
	add_action("talk", "talk");
	add_action("finish","finish");		
}

int talk()
{
	tell_room(environment(this_player()),"Business Agent sayes, \"So, your looking for a job? Lets see what I can dig up.\"\n");
	write("Business Agent sayes, \"So, your looking for a job? Lets see what I can dig up.\"\n");
	tell_room(environment(this_player()),"The Business Agent begins to dig through his files looking for something suitable.\n");
	write("The Business Agent begins to dig through his files looking for something suitable.\n");
	
	call_out("FindJob",5);
	return 1;
}

int finish()
{
	object *inv;
	tell_room(environment(this_player()),"Business Agent sayes, \"So, you've come back with it? I hope it wasn't to much trouble.\"\n");
	write("Business Agent sayes, \"So, you've come back with it? I hope it wasn't to much trouble.\"\n");
	
	
	inv=all_inventory(this_player());
	for(int i=0; i<sizeof(inv); i++)
	{
		if(is_a(TRAP,inv[i]))
		{
			if(inv[i]->getTrapedGhostID()==100000)
			{
				tell_room(environment(this_player()),"Business Agent sayes, \" Aha, there it is. Keep up the good work.\"\n");
				write("Business Agent sayes, \" Aha, there it is. Keep up the good work.\"\n");
				tell_room(environment(this_player()),"The Business Agent takes the trap from you and hands you some cash.\n");
				write("The Business Agent takes the trap from you and hands you some cash.\n");
				this_player()->set_cash(this_player()->get_cash()+(5000*(random(5)+1)));
				destruct(inv[i]);
				this_player()->setNewbieJobTotal(this_player()->getNewbieJobTotal()+1);
				return 1;
			}
		}
	}
	tell_room(environment(this_player()),"Business Agent sayes, \" Doesn't look like you have any traps filled with my ghosts. Come back when you do.\n\"");
	write("Business Agent sayes, \" Doesn't look like you have any traps filled with my ghosts. Come back when you do.\n\"");
	return 1;
}


void FindJob()
{
	int rand;
	object ghost;
	rand=random(5)+1;
	tell_room(environment(this_player()),"The Business Agent takes a deep breath and sayes, \"Its in the old cemetery, should be easy for someone like you. Go ahead and round it up. Bring the trap back here.\"\n");
	write("The Business Agent takes a deep breath and sayes, \"Its in the old cemetery, should be easy for someone like you. Go ahead and round it up. Bring the trap back here.\"\n");
	ghost=clone_object("/obj/npcs/ghosts/bizghost.c");
	ghost->move("/areas/cemetery/cemetery"+rand+".c");
	this_player()->setNewbieJobTime(time());
	this_player()->setNewbieJob(1);
}

void greet()
{
	write("Business Agent sayes, \"Welcome, How can I help you?\"\n");
	tell_room(environment(this_player()),"Business Agent sayes, \"Welcome, How can I help you?\"\n");		
}
