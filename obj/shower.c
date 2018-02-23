inherit OBJECT;



void create()
{
        ::create();
    set_id(({"shower", "Shower"}));
    set_short("a shower.");
    set_long("a shower with a glass door mounted onto the wall..");
    set("prevent_get", 1);

    
}


void init()
{
        add_action("shower","shower");
}






int shower(string arg)
{

    write("You step into a shower and begin to wash yourself clean.\n\n");
    
    say(this_player()->query_cap_name() + " steps into the shower and begins to wash
themselves.\n");
        call_out("finish",10);



    return 1;
}

void finish()
{
        if(this_player()->CheckForStatus("slimed"))
    {
         write("You feel the slime finally leave your body\n");         
         this_player()->ClearStatus("slimed");
    }
    write("You finish your shower and turn off the water.\n");
    say(this_player()->query_cap_name() + " finishes in the shower and turns off the
water.\n");
        
        
}
