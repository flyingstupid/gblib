//
//  /obj/train/dodgetrainer1.c
//  GB Mud
//
//  Created by Krista Jastrzembski on 1/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

inherit "/obj/train/trainer.c";


void create()
{
    set_id(({"Trainer", "trainer", "machine", "tennis ball machine"}));
    set_short("Tennis ball machine");
    set_long ("As old dilapdated tennis ball machine");
    setTrainerSkill("dodge");
    setDifficulty(50);
    setStart ("You flip the switch and the tennis ball machine starts with an alarming rattle.");
    setFinish ("The tennis ball machine clunks loudly and shuts down.");
    setCritFailure("You are pummelled relentlessly by the tennis balls until you fall to the floor in a crumpled heap");
    setCritSuccess("You dodge the incoming tennis balls with skill and finesse");
    setFailure("You are pummeled by the tennis balls");
    setSuccess("You dodge the tennis balls successfull and emergy relatively unscathed.");
    
    
    
}

