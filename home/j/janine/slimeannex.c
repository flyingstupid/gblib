//
//  /home/j/janine/slimeannex.c
//  GB Mud
//
inherit "/areas/research/slimeroom.c";


void create()
{
    ::create();
    
    set_exits( ([
                 "lab" : "/home/j/janine/lab.c",
                ]) );
}