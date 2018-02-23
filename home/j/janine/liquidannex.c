//
//  /home/j/janine/liquidannex.c
//  GB Mud
//
inherit "/areas/research/liquidroom.c";


void create()
{
    ::create();
    
    set_exits( ([
                 "lab" : "/home/j/janine/lab.c",
                 ]) );
}