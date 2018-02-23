//  /areas/demo/demo6.c
//  Character Generation Room!
//
//   -Critical

inherit ROOM;

void create()
{
    set_light(1);
    set_short("Character Generation Room");
    set_long(
             "This is the character generation room. Here you can SET your skills along with CHECKing them to be sure your on par with your point spending.  You may also SETLONG and SETSHORT to setup how your character is viewed and once your all set you can finalize your character by using DONE!"             );
    set_exits( ([
                 "out" : ({ "/areas/demo/demo1.c"}),
                 ]) );
    set_ghost_ok(0);
    
}



void init()
{
        //add_action("quick","quick");
        add_action("setshort","setshort");
        add_action("setlong","setlong");
        add_action("done", "done");
        add_action("skillset","set");
        add_action("reset", "reset");
        add_action("check", "check");
}

// set
// This function allows the player to set his skills. 
// set <skill> <value>

int skillset( string arg )
{
        string skill;   
        int value;
        
        if(this_player()->CharGenOK())
        {
                write("Your already done with character generation!\n");
                return 1;
        }
                
        if(!arg)
        {
                write("Syntax: set <skill> <value>\n");
                return 1;
        }
        
        sscanf(arg,"%s %d",skill,value);
        
        if(skill == "aim" || skill == "dodge" || skill == "block" || skill ==
"scan" || skill == "firstaid" ||skill == "roll" || skill == "research" ||
skill == "collection" || skill =="throw")
        {  
        
        
                if(value<1)
                {
                        write("Values must be postive.\n");
                        return 1;
                }
                if(value>75)
                {
                        write("Values may not be above 75.\n");
                        return 1;       
                }
                if(value<30 && value>1)
                {
                        write("Values must be at least 30\n");
                        return 1;       
                }
                
                write("You set " + skill + " to " + value + ".\n");
                this_player()->set_skill(skill,value);
                return 1;
        }
        else
        {
                write(skill + " isnt a valid skill!\n");
                return 1;       
        }
                
}

int check()
{
        int total;
        mapping mskills=this_player()->get_skills();
        int *skills = values(mskills);  
        
        if(!skills)
        {
                write("You need to have skills first!\n");
                return 1;
        }
        
        for(int i=0; i < sizeof(skills); i++)
        {
                total = total + skills[i];      
        }
        
        write("You have spent " + total + " out of 550\n");     
        
        return 1;       
}

int setshort(string arg)
{
        if(!arg)
        {
                write("SYNTAX: setshort <desc>\n");     
                return 1;
        }       
        
        write("You set your short to: " +arg+"\n");
        this_player()->set_short(arg);
        
        
        return 1;
}

int setlong(string arg)
{
        if(!arg)
        {
                write("SYNTAX: setlong <desc>\n");      
                return 1;
        }       
        
        write("You set your long to: " +arg+"\n");
        this_player()->set_long(arg);
        
        
        return 1;
}

void reset()
{
        write("Are you sure you want to reset? (Y/N)"); 
        input_to("resetOK");
}

int resetOK ( string arg )
{
        mapping skills;
        
        if(arg=="y")
        {
                skills=this_player()->get_skills();
                write("Alright then! Removing your skills!\n");
                for(int i=0; i <sizeof(keys(skills));i++)
                {
                        this_player()->set_skill(values(skills[i]),0);  
                }
                return 1;
        }
        else
        {
                write("Alright, aborting!");
                return 1;
        }
}

int done()
{
        int newtotal;
        int total;
        mapping mskills=this_player()->get_skills();
        int *skills = values(mskills);  
        
        
        if(this_player()->CharGenOK())
        {
                write("Your already done with character generation!\n");
                return 1;
        }
        
        if(!skills)
        {
                write("You need to have skills first!\n");
                return 1;
        }
        
        for(int i=0; i < sizeof(skills); i++)
        {
                total = total + skills[i];      
        }
        
        if(total<550)
        {
                newtotal=550-total;
                write("You still have " + newtotal +" points to spend!\n");
                return 1;       
        }
        if(total>550)
        {
                newtotal=total-550;
                write("You over by " + newtotal + " points!\n");
                return 1;       
        }
        if(total==550)
        {
                write("Your all set and ready for action!\n");
                this_player()->set_cash(5000);
                write("Giving you a little bit of cash!\n");
                this_player()->SetCharGenOK(1); 
                return 1;       
        }
}
