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
    write("This is a test of the color system\n");
    write("This is a test of the color system\n");
    write("%^BLUE%^ This text should be BLUE %^BLUE%^\n");
    return 1;
}
