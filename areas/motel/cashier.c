//
//  /areas/motel/cashier.c
//  GB Mud
//
//  Created by Krista Jastrzembski on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

inherit NPC;


void setup()
{
    set_living_name("Cashier");
    set_name("Cashier");
    set_short("A greasy cahsier stands behind the counter");
    set_long("He's a greasy cashier who lears are you suspiciously.\n");
    set_id( ({"cashier"}) );
    //isShop();
    setReplies( ([
                  "job" : "What you do you think my job is you idiot, I rent out rooms.  You looking for a room?",
                  ]) );
}
