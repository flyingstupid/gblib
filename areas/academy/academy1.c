inherit ROOM;

void create()
{
     set_light(1);
     set_short("Welcome to the Academy");
     set_long(
          "Hello and welcome to Ghostbusters! Here is where we will teach you how to\n"
          "play the game. First we will cover basic functions then we'll show you how\n"
          "to catch you first ghost. Finally we'll show you how you can become the\n"
          "most famous ghost buster that's ever lived. To begin your adventure LOOK\n"
          "SIGN. (Type: LOOK SIGN)\n"
     );
     set_exits( ([
           "north" : "/areas/academy/academy2.c",

]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "This room will cover the commands of: LOOK, WHO, CHAT, VMAP, movements\n"
               "\n%^GREEN%^LOOK%^RESET%^:This command lets you see the description of the room you are\n"
               "currently in. When you move you will automatically look. Give it a try\n"
               "\n%^GREEN%^WHO%^RESET%^:This command shows you who is online. Give this one a try!\n"
               "\n%^GREEN%^CHAT%^RESET%^: this command helps you talk to the mud. You use it like this\n\n"
               "chat hello!\n\n"
               "This will display to the mud, 'chat: YourName: Hello!'\n\n"
               "%^GREEN%^VMAP%^RESET%^: VMAP or virtual map, tells in a graphical way, whats around you and\n"
               "what directions are availible to you. The Red Dot is you, Blue are other\n"
               "players and green are NPCs or ghosts.\n\n"
               "%^GREEN%^MOVEMENT%^RESET%^: Movement uses all directions that you will see displayed under\n"
               "Exits. Simply type the first letter of the direction you wish to move\n"
               "So, go move on, simply type n or north.\n"

,]) );
}
