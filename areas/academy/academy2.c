inherit ROOM;

void create()
{
     set_light(1);
     set_short("Into to the Academy");
     set_long(
          "Now that we have basic commands down its time for you to understand the purpose \n"
          "of our game. We are a heavy Roleplaying enforced player verses NPC but also a   \n"
          "'guild' verses 'guild'. Our main job is to make a world that you can play in and\n"
          "have fun. Our primary way of gauging success has nothing to do with XP or PKing.\n"
          "Money makes the world go round. So remember that being able to get money is what\n"     
          "makes you attractive to franchises! LOOK SIGN for more details\n"
); 
     set_exits( ([
           "south" : "/areas/academy/academy1.c",
           "north" : "/areas/academy/academy3.c",

]) );
     set_items( ([
          "sign" : "%^GREEN%^What's a Franchise?%^RESET%^\n"
                   "\tA franchise is what we call guilds or clans in other games.\n"
                   "Players will have the ability to start their own which will give them access to\n"
                   "more powerful gear, better jobs, storage of powerful gear such as cars and\n"
                   "containment units. To start a franchise you need to go to a bank to get a loan.\n\n",
]) );
}
