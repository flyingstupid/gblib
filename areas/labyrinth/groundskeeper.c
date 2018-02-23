//
//  /areas/labyrinth/groundskeeper.c
//  GB Mud
//

inherit "/std/area/mobiles/shopkeep.c";

void setup()
{
    set_living_name("groundskeeper");
    set_name("groundskeeper");
    set_short("A groundskeeper shuffles around the room");
    set_long("Hes an average groundskeeper.\n");
    set_id( ({"grounds", "keeper", "Groundskeeper", "groundskeeper",}) );
    isShop();
    //askOk();
    setReplies( ([
                  "job" : "I keep the grounds of this here park as clean as I can....considering.",
                  "park" : "Oh, the city put this park in a few years back, for a while it was a lovely spot until everythign went wrong",
                  "wrong" : "An unsavory group o' folks started using the park for dark and nefarious deeds",
                  "deeds" : "Well, now, I don't claim to know half of what went on here...alls I know is that what should be dead don't always stay that way no more.",
                  "dead" : "Yep, city's been trying to get the populace to help clear them up...in fact, if you wanted to help I'd be happy to get you some gear and give you some tips",
                  "tips" : "well...that path to the west is probably the easiest, wile the path there to the north, well..that one there seems the worst hit by them undead goons.",
                  "gear" : "well, sure 'nuff....you just holler out the word EQUIP and I'll be happy to set you up with some basic gear.",
                  ])  );
}