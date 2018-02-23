inherit COMMAND;


int main(string arg)
{
	int test;
	string tempShort;
	object ob;
	//object jar;
	//object *inv;
	
	ob = present(arg, environment(this_player()));
	
	if(!ob)
    	return(notify_fail("You can't find that here!\n"));
        
    if(ob->query("prevent_get") || ob->prevent_get())
        return(notify_fail("That is to big to collect!\n"));
	
        
        
    
    

        
        
    test=this_player()->DoSkillRoll("collection");
        
    if(test<1)
    {
    	write("You get a " + ob->query_short() + "\n");
    	say(this_player()->query_cap_name() + " skillfully collects " + ob->query("short") + ".\n");
    	tempShort=ob->query("short");
    	ob->set_id(({"jar", "sample", ob->query_id()}));
		ob->set_short("a jar that contains " + tempShort);
    	ob->move(this_player());
  
    	return 1;
	}
	else
	{
		
		say(this_player()->query_cap_name() + " fumbles " + ob->query("short")+ " and barely contains it!\n");
		write("You fumble with " + ob->query("short")+ " and barely contain it!\n");
		//ob->SetResearchValue(ob->GetResearchValue/2);
		//ob->SetWasFumbled(1);
		tempShort=ob->query("short");
		ob->set_id(({"jar", "sample", ob->query_id()}));
		ob->set_short("a jar that contains " + tempShort);
		ob->move(this_player());
		return 1;
	}
	
	
	
	
}


int query_wait_type( string arg )
{
    return 3;
}

int query_wait_time( string arg )
{
    return 3000;
}
