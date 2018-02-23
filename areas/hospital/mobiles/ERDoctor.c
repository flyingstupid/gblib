//
//  /areas/hospital/mobiles/docterER.c
//  GB Mud
//
//  Critial @ 1-22-12
//
//   DoctorER is the mobile which players pay to get healed.

inherit NPC;

void setup()
{
   set_living_name("doctor");
   set_name("doctor");
   set_short("ER doctor");
   set_long("He's the ER Doctor here to over see your recovery. You may have him DIAGNOSE you and HEAL your injuries or even TREAT your ailments.\n");
   set_id( ({"doc", "doctor", "Doc", "Doctor", "er", "ER"}) );
   setReplies( ([
                 "job" : "Well, I work here at the hospital. Helping
folks get better after accidents",
                 ])  );
}

void init()
{

       add_action("diagnose","diagnose");
       add_action("heal","heal");
       add_action("treat","treat");

}


int diagnose()
{

    string *injuries;
    int damagecost;
    int num=0;
      
        
        injuries = this_player()->keys(this_player()->get_statuses());
       
        write("The ER Doctor turns toward you and sayes, \"Lets take a look at you\"\n");
        say("The ER Doctor turns toward " + this_player()->query_cap_name() + " and sayes, \"Lets take a look at you\"\n");
        
        if(this_player()->get_health()<100)
        {
                damagecost=(100-this_player()->get_health())*5;
                
                write("The ER Doctor sayes, \"Well your battered up, I can fix you up for $"+ damagecost+"\n");
                say("The ER Doctor sayes, \"Well your battered up, I can fix you up for $"+ damagecost+"\n");      
                num++;
        }
        
    for(int i=0; i < sizeof(injuries); i++ )
    {
                injuries[i];
               
                if(injuries[i]=="slimed")
            {
	            		write("The ER Doctor adds, \"Your covered in slime, we can scrub you clean of course for $50!\"\n");
                        say("The ER Doctor adds, \"Your covered in slime, we can scrub you clean of course for $50!\"\n");
                        num++;
                }
                
    }
                
    if(num<0)
    {
	    write("The ER Doctor finishes, \"Thats all I can find wrong with
you at least.\"\n");
        say("The ER Doctor finishes, \"Thats all I can find wrong with
you at least.\"\n");   
    }
        else
        {
	        write("The ER Doctor shakes his head at you and sayes, \"You seem to be fine to me\".\n");
            say("The ER Doctor shakes his head at "+
this_player()->query_cap_name()+" sayes, \"You seem to be fine to me\".\n");
        }


        return 1;
}


int heal()
{
        
        int costAmount=(100-this_player()->get_health())*500;
        
        if(!costAmount)
        {
                write("Error! Tell Critical!\n");       
                return 1;
        }
        
        if(this_player()->get_cash()>costAmount)
        {
	        write("The ER doctor gathers some supplies and patches up you\n");
            say("The ER doctor gathers some supplies and patches up " +
this_player()->query_cap_name() + "\n");
                write("This costs you: $"+ costAmount/100 +"\n");   
                this_player()->set_cash(this_player()->get_cash()-costAmount);
                this_player()->set_health(100);
        }
        else
        {
	        write("The ER Doctor sayes, \"You dont have the cash to cover
this! I dont work for free!\"\n");
            say("The ER Doctor sayes, \"You dont have the cash to cover
this! I dont work for free!\"\n");      
        }
        return 1;

}

int treat(string arg)
{
        
        
        int costAmount;

        
        if(!arg)
        {
                write("SYNTAX: treat <thing>");
                return 1;       
        }       
        
        if(arg=="slimed")
        {
                costAmount=5000;
                if(this_player()->get_cash()>costAmount)
                {
	                write("The ER Doctor orders in some nurses to clean the
slime off of you\n They finish quickly.\n");
                    say("The ER Doctor orders in some nurses to clean the
slime off of "+this_player()->query_cap_name()+"\n They finish quickly.\n");
                        this_player()->ClearStatus("slimed");
                
this_player()->set_cash(this_player()->get_cash()-costAmount);
                }       
                else
                {
                        write("You can't afford this service!");
                                
                }       
                return 1;
        }
        else
        {
                write("You aren't affected that way!\n");       
                return 1;
        }
        
        
}
