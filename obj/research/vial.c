//
//  /obj/research/vial.c
//  GB mud
//
//  Created by Krista Jastrzembski on 8/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

inherit "/obj/research/vessel.c";


void create()
{
    ::create();
    
    set_id(({"vial"}));
    set_short("glass vial");
    set_long ("a glass vial with a screw top");
    SetFill(0);
    set_type("vial");
    
}
