//
//  research.c
//  GB mud
//  /cmds/std/research.c




inherit COMMAND;

int DoResearchDisplay();
void DoResearchExamine(object item);
void DoResearchPrepare(object item);
//void DoResearchExtract(object item);

string GetCommand( string arg );
object GetItem( string arg );

/*Variables*/


int main(string arg)
{
	string cmd;
	object sample;
    int labSpace;
    
	if( !arg || arg == "" )
	{
        return DoResearchDisplay();
	}
    
    cmd = GetCommand( arg );
    sample = GetItem( arg );
    

	if(cmd=="examine")
	{
        
		if(!sample)
		{
            write( "The object could not be examined or could not be found\n" );
		}
		else
		{
			write("You begin your research on: " + sample ->query_short() +".\n");	
			DoResearchExamine(sample);
		}
		return 1;	
	}
	
	if(cmd=="prepare")
    {

        
        if (!sample)
        {
            RESEARCH_D->DisplayPreps();
        }
		labSpace = this_player()->get_skill("research")/10;
        
        //write("you have a total of " + labSpace + " spots in your lab.\n");
        //write("You are currently preparing " + this_player()->GetNumProjects() + " projects.\n");
        
		if(this_player()->GetResearchTotal()<10)
		{
			return(notify_fail("You don't know the first thing about preparing items\n"));
		}
        else if(!sample)
		{
            RESEARCH_D->displaypreps();
            //tell_object( this_player() , "error 0");
            //return(notify_fail( "The object could not be prepared or could not be found\n" ));
		}
        else if(this_player()->GetNumProjects() >= labSpace){
            return(notify_fail( "There is no room in your lab at this time\n" ));
        }
     
        else
		{
			DoResearchPrepare(sample);
		}
		return 1;
		
	}
    
    return 0;
}

int DoResearchDisplay()
{
    string researchString;
    string commandString = "Examine";
    
    if(this_player()->GetResearchTotal() >= 10000 )
    {
        commandString +=", Prepare";
    }
    
    if(this_player()->GetResearchTotal() >= 20000 )
    {
        commandString +=", Extract";
    }
    
    researchString = 
    "===============================[RESEARCH]===================================\n";
    researchString += "Research Notes for: " + this_player()->query_cap_name() + "\n";
    researchString += "Skills -- Research: "+this_player()->get_skill("research")+"  Collection: "+this_player()->get_skill("collection")+ "  Invention: "+this_player()->get_skill("invention") + "\n";
    researchString += sprintf("%sResearch Points:%s %d \n","","",to_int(this_player()->GetResearchCurrent()));
    researchString += "Life Time Points: " + this_player()->GetResearchTotal() + "\n";
    researchString += "Commands: "+ commandString +"\n";
    researchString += "You are currently preparing " + this_player()->GetNumProjects() + " samples\n";
    researchString +=
    "============================================================================\n";
    
    write(researchString);
    return 1;
}

void DoResearchExamine(object item)
{
	int skillTest;
	
    
	skillTest=this_player()->DoSkillRoll("research", item->GetResearchDiff());
	
	if(skillTest<1)
	{
		float tempValue = item->GetResearchValue()*item->GetResearchQuality();
		
		write("After a long time of heavy research you discover things about your sample
              you hadn't known before.\n");
		this_player()->SetResearchCurrent(this_player()->GetResearchCurrent()+tempValue);
        
        this_player()->SetResearchTotal(this_player()->GetResearchTotal()+item->GetResearchValue());
		destruct(item);
	}
	else
	{
		write("Something goes wrong and your sample is destroyed!");	
		destruct(item);
		
	}
    
}



void DoResearchPrepare(object item)
{
    
	int skillTest;
	
	if(item->GetResearchPrepared()==1)
	{
		write("This item has already been prepared\n");
		
	}
	else
	{
		skillTest=this_player()->DoSkillRoll("research", item->GetResearchDiff());
        
		if(skillTest>1)
		{
			item->SetResearchPrepared(1);
            //write ("This item will require " + item->GetPrepTime() + " minutes to prepare\n");
			
			if(skillTest>20)
			{
                item->SetResearchQuality(item->SetResearchQuality() + 1);
                //write("You prepare " + item->query_short() +" to be better understand it when someone examines it.\n");
			}
			else if(skillTest>40)
			{
                item->SetResearchQuality(item->SetResearchQuality() + 1.2);
                //write("You prepare " + item->query_short() +" to better understand it when someone examines it.\n");
			}
			else if(skillTest>60)
			{
                item->SetResearchQuality(item->SetResearchQuality() + 1.5);
                //write("You prepare " + item->query_short() +" to better understand it when someone examines it.\n");
			}
			else if(skillTest>80)
			{
                item->SetResearchQuality(item->SetResearchQuality() + 1.8);
                //write("You prepare " + item->query_short() +" to better understand it when someone examines it.\n");		
			}
            
            this_player()->SetNumProjects(1);
            //this line is just to keep me from having 9 million active projects during testing.
            //this_player()->SetNumProjects(-1);
            
            RESEARCH_D->AddProject(item, this_player());
            destruct(item);
			
		}
		else
		{
			write("Something goes wrong and your sample is destroyed!");
			destruct(item);
            
		}
        
        
	}
    
}

string GetCommand( string arg )
{
    string cmd, itemName;
    
    if( sscanf(arg, "%s %s", cmd, itemName) != 2 )
    {
        return arg;
    }
    
    return cmd;
}

object GetItem( string arg )
{
    string cmd, itemName;
    object item;
    
    
    
    if( sscanf(arg, "%s %s", cmd, itemName) != 2 )
    {
        return 0;
    }
    
    item = present( itemName, this_user() );
    
    if( !item ){
        write("Item isn't here\n");
        return 0;

    }
    
    
    else if(!is_a( SAMPLE, item ) )
    {
        write("Not a sample\n");
        return 0;
    }
    
    //write("found sample");
    return item;
}


/*int query_wait_type( string arg )
{
	if( !arg || arg == "" )
	{
        return 5;
	}
    
    return 3;
}

int query_wait_time( string arg )
{
	
	string cmd;
	object sample;
	
	
	if( !arg || arg == "" )
	{
        return 0;
	}
	
    
	
	cmd = GetCommand( arg );
    sample = GetItem( arg );
    
    
    if(cmd=="examine")
    {
	    return sample->GetResearchTime()*1000;
    }
    else if(cmd=="prepare")
    {
	    return sample->GetResearchTime()*2000;
    }
    else
    {
	 	return 1000;   
    }
	
	
    return 0;
}*/
