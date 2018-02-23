//
//  /areas/motel/motel0.c
//  GB Mud
//
//  Created by Krista Jastrzembski on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

inherit ROOM;

/* Variables */
object cashier;

void create()
{
    set_light(1);
    set_short("Motel Office");
    set_long(
             "This is the rental office of a seedy motel.  A long,\n"
             "filthy counter stands between you and the cash register, \n"
             "operated by a greasy haired man who lears are you suspiciously. \n"

             );
    set_exits( ([
                 "west" : "/areas/motel/motel4.c",
                 "north": "/areas/motel/motel10.c",
                 "south": "/areas/motel/motel11.c",
                
                 ]) );
    set_items( ([
                 "dusty plant" : "An old platic plant sits in the corner, it is comvered in dust and looks as though it hasn't been touched in years.\n",
                 "dusty plant" : "An old platic plant sits in the corner, it is comvered in dust and looks as though it hasn't been touched in years.\n"
                 ]) );    

    cashier=clone_object("/areas/motel/cashier.c");
    cashier->move("/areas/motel/motel0.c");
}
