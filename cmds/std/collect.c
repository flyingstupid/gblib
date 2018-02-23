//
//  /cmds/std/collect.c
//  GB mud
//



inherit COMMAND;

/* Function Prototypes */
int HasContainer(object ob);


int main(string arg)
{
	int test;
	object ob;
    object vessel;
    object collectedSample;
    string sampleType;
   	
	ob = present(arg, environment(this_player()));
	    
	if(!ob)
    	return(notify_fail("You can't find that here!\n"));
    
    if(ob->query("prevent_get") || ob->prevent_get()){
        return(notify_fail("That is to big to collect!\n"));
    }
    vessel = present(ob->get_vessel(), this_player());
    
	if (!vessel){
        return(notify_fail("You don't seem to have a " + ob->get_vessel() + ".\n"));
    }

    test=this_player()->DoSkillRoll("collection", ob->get_collect_diff());
    
    if(test>1)
    {
    	int value;
        float value1;
        
        value1 = (test/75.0)+1;
        write("test is " + test + ".\n"); 
        write("value 1 is " + value1 + ".\n"); 
        value = (ob->get_base_value() * value1);
        write("value is " + value + ".\n"); 
        
        sampleType = ob->get_type();
        write ("SampleType is " + sampleType + ".\n");
        collectedSample = clone_object("/obj/research/collected" + sampleType + ".c");
        collectedSample->set_examine_value(value);           
        
        
    	say(this_player()->query_cap_name() + " skillfully collects " + collectedSample->query("short") + ".\n");
        write("You get a " + collectedSample->query_short() + "\n");
        destruct(vessel);
        destruct(ob);
        collectedSample->move(this_player());
        

        return 1;
    }
    if (test< -20){
        write("You fumble with the " + ob->get_vessel()+ " and it is destroyed, contaminating the sample beyond recovery!\n");
        destruct(vessel);
        destruct(ob);
		return 1;
    }
	else
	{
    	sampleType = ob->get_type();
        write ("SampleType is " + sampleType + ".\n");
        collectedSample = clone_object("/obj/research/collected" + sampleType + ".c");
        collectedSample->set_examine_value(100);    
        
        
        say(this_player()->query_cap_name() + " fumbles " + ob->query("short")+ " and barely contains it!\n");
		write("You fumble with " + ob->query("short")+ " and barely contain it!\n");
        destruct(vessel);
        destruct(ob);
            
        collectedSample->move(this_player());

		return 1;
	}
}

/*int HasContainer(object ob){
    
    object *playerInv;
    
    tell_object( this_player(), "you need a " + ob->get_vessel() + " to collect this.\n" );
    
    if (
    playerInv = all_inventory(this_player());
    for( int i = 0; i < sizeof( playerInv ); i++ ){
        if (is_a ("obj/research/vessel.c", playerInv[i] ) && (playerInv[i]->GetType() == ob->get_vessel())){
         tell_object( this_player() , "great, you have a " +ob->get_vessel() + " in your inventory!\n");   
            return i+1;
        }
    }
    return 0;
}*/



int query_wait_type( string arg )
{
    return 3;
}

int query_wait_time( string arg )
{
    return 3000;
}