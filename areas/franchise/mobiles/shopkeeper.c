//
//  /areas/franchise/mobiles/shopkeeper.c
//  GB Mud
//
//  Created by Krista Jastrzembski on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

inherit "/std/area/mobiles/shopkeep.c";

void setup()
{
    set_living_name("shopkeeper");
    set_name("Franchise Shopkeeper");
    set_short("A shopkeeper stands behind the counter");
    set_long("Hes an average shopkeeper.\n");
    set_id( ({"shop", "keeper", "Shopkeeper", "shopkeeper",}) );
    isShop();
    //askOk();
    setReplies( ([
                  "job" : "Well, I work here at the shop, selling gear to new ghostbusters!",
                  ])  );
}


