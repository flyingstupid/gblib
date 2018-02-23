inherit ROOM;

//Functions
int pourcoffee();
int makecoffee();
void setcoffeefill(int fill);
int getcoffeefill();
string getcoffeestring();

//Variables
object coffee;
int coffeefill=0;


void create()
{
     set_light(1);
     set_short("The Breakroom");
     set_long(
          "A small room with 2 doors and some stairs. There are\n"
          "lockers on the walls and a kitchen set built into a\n"
          "old looking counter. A small table with 4 chairs sits\n"
          "in the middle of the room. Sitting on the counter is an\n"
          "old coffee maker that looks like it still works.\n"
     );
     set_exits( ([
          "east" : "/areas/franchise/franchise3.c",
          "west" : "/areas/franchise/franchise2.c",
          "north": "/areas/franchise/franchise5.c",
          "south": "/areas/franchise/franchise.c",
          "down" : "/areas/franchise/franchise4.c",
          "up"   : "/areas/franchise/franchise6.c",
     ]) );
     set_items( ([
                 "coffee maker" : "You can MAKECOFFEE with this old thing. Then you can POURCOFFEE so you can enjoy your labors.\n",
                 "coffeemaker" : "You can MAKECOFFEE with this old thing. Then you can POURCOFFEE so you can enjoy your labors.\n"


      ]) );    
}

void init()
{
   add_action("makecoffee","makecoffee");
   add_action("pourcoffee","pourcoffee");
   add_action("checkcoffee","getcoffeestring");
}

int makecoffee()
{

   if(getcoffeefill()>0)
   {
        write("There is still some coffee left.\n");
   }
   else
   {
   setcoffeefill(10); 
   write("You take some coffee and pour it into the coffee maker. After pouring water into the coffee maker and pushing a few buttons the machine it bubbles and brews. After a few moments the pot fills up to the brim.\n"); 
   say(this_player()->query_name() + " starts to brew some coffee. After a few moments the refreshing smell of coffee fills the room.\n"); 
   }

   return 1;
}

int pourcoffee()
{
   if(coffeefill==0)
   {
       write("The coffee pot is empty.\n");
       return 1;
   }

   write("You pour yourself a mug of coffee.\n");
   say(this_player()->query_name() +" pours themselves a mug of coffee.\n");

   setcoffeefill(coffeefill-1);
   coffee=clone_object("/obj/drinks/coffee.c");
   coffee->move(this_player());

   return 1;
}

void setcoffeefill(int fill)
{
    coffeefill=fill;
}


int getcoffeefill()
{
    return coffeefill;
}

string getcoffeestring()
{
    if(coffeefill==0)
    {
     return ("The coffee pot is empty.");
    }
    else if(coffeefill > 1 && coffeefill < 5)
    {
    return ("The coffee pot is half filled.");
    }
    else if(coffeefill > 5 && coffeefill < 10)
    {
    return ("The coffee pot is almost full.");
    }
    else
    {
    return ("The coffee pot is full.");
    }
}


