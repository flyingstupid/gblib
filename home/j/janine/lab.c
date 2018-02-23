//
//  /home/j/janine/lab.c
//  GB Mud
//

inherit "/areas/research/labroom.c";


void create()
{
    ::create();
    
    set_exits( ([
                 "workroom" : "/home/j/janine/workroom.c",
                 "slime" : "/home/j/janine/slimeannex.c",
                 "liquid" : "/home/j/janine/liquidannex.c",
                ]) );
    
}