//
//  /cmds/std/test.c
//  GB Mud
//
//  Created by Krista Jastrzembski on 1/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



inherit COMMAND;

void fun();


int main(){
    call_out("fun", 3);
    write("end\n");
    return 1;
}

void fun(){
    tell_object (this_player(), "success");
    write("success\n");
    return;
}
