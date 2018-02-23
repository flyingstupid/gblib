//
//  collect.c
//  GB mud
//
//  Created by Krista Jastrzembski on 8/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


inherit COMMAND;

/* Function Prototypes */
int HasContainer(object ob);


int main(string arg)
{
	int test;
	string tempShort;
	object ob;
    //object *playerInv;
    
    
	//object jar;
	//object *inv;
	
	ob = present(arg, environment(this_player()));
	
	if(!ob)
    	return(notify_fail("You can't find that here!\n"));
    
    if(ob->query("prevent_get") || ob->prevent_get()){
        return(notify_fail("That is to big to collect!\n"));
    }
    
	if (!HasContainer(ob)){
        return(notify_fail("You don't seem to have a " + ob->GetVessel() + ".\n"));
    }

    test=this_player()->DoSkillRoll("collection");
    
    if(test<1)
    {
    	write("You get a " + ob->query_short() + "\n");
    	say(this_player()->query_cap_name() + " skillfully collects " + ob->query("short") +
            ".\n");
    	tempShort=ob->query("short");
    	ob->set_id(({"jar", "sample", ob->query_id()}));
		ob->set_short("a jar that contains " + tempShort);
    	ob->move(this_player());
        
    	return 1;
	}
	else
	{
		
		say(this_player()->query_cap_name() + " fumbles " + ob->query("short")+ " and
            barely contains it!\n");
		write("You fumble with " + ob->query("short")+ " and barely contain it!\n");
		//ob->SetResearchValue(ob->GetResearchValue/2);
		//ob->SetWasFumbled(1);
		tempShort=ob->query("short");
		ob->set_id(({"jar", "sample", ob->query_id()}));
		ob->set_short("a " + ob->GetVessel() + " that contains " + tempShort);
		ob->move(this_player());
        destruct(ob->GetVessel());
		return 1;
	}
}

int HasContainer(object ob){
    
    object *playerInv;
    
    tell_object( this_player(), "you need a " + ob->GetVessel() + "to collect this.\n" );
    playerInv = all_inventory(this_player());
    for( int i = 0; i < sizeof( playerInv ); i++ ){
        
        tell_object( this_player(), "looking in your inventory\n" );
        if (is_a ("obj/research/vessel.c", playerInv[i] ) && (playerInv[i]->GetType() == "vial")){
         tell_object( this_player() , "great, you have a " +ob->GetVessel() + "in your inventory!\n");   
            return 1;
        }
        else{
            tell_object( this_player() , "Sorry, you don't seem to have a " +ob->GetVessel() + " in your inventory!\n");
            return 0;
        }

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
