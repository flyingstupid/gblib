//
//  /cmds/std/examine.c
//  GB mud
//



inherit COMMAND;


/* function prototypes */

int examine(object sample);

/*Global Variables*/
object sample;

int main(string arg)
{
    sample = present( arg, this_player() );
    
    if(!arg)
    {
        RESEARCH_D->DisplayPreps();
        return 1;
    }
    if(!sample)
    {
        return(notify_fail("You do not have that type of sample in your possession.\n"));
    }
    else 
    {
        examine(sample);
    }
    return 1;
}


int examine(object sample)
{
    int LabSpace;
    //Lab space - there should be sufficient lab space in the franchise...I think players should start with 5 spots and be able to buy lab bench expansions as time goes on.
    //LabSpace = this_player->get_lab_space();
    LabSpace = 5;
    if(this_player()->GetNumProjects() >= LabSpace){
        return(notify_fail( "There is no room in your lab at this time.\n" ));
    }
    tell_object(this_player(), "You begin the process of examining " + sample->query_short() + "\n");
    RESEARCH_D->AddProject(sample, this_player());
    destruct(sample);
    return 1;
}
