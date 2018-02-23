//
//   /obj/vermincontainmentunit.c
//


/*
 #define TYPE     0
 #define GHOSTID  1
 #define POWER    2
 */

inherit OBJECT;

/** Function Prototypes **/
void set_space(int setSpace);
void set_ghosts(string type, int ghostID, int power);
int get_space();
array get_ghosts();
int clean(string arg);

/** Varibles **/
array ghosts;
int space;

void create()
{
    set_id(({"unit", "contrainment"}));
    set_short("containment unit");
    set_long("A massive solid metal wall hung container with heavy rivets sealing it tightly.\n" +
             "It has two lights behind metal cages, one red the other green. There is\n"+
             "a slot for traps to be inserted and a lever to be pulled to clean traps\n"+
             "\"Property of GB City is stamped across the fron of the machine\n");
             set_space(1000);
             set("prevent_get", 1);
             }
             
             void init ()
             {
                 add_action("cleantrap", "cleantrap");
                 
             }
             
             
             void set_space(int setSpace)
             {
                 space=setSpace;
             }
             
             
             void set_ghosts(string type, int ghostID, int power)
             {
                 ghosts +=({type, ghostID, power});
             }
             
             
             int get_space()
             {
                 return space;
             }
             
             
             array get_ghosts()
             {
                 return ghosts;
             }
             
             int cleantrap(string arg)
             {
                 
                 object ob;
                 string target;
                 int tempCash;
                 if( !arg || arg == "" )
                 {
                     write("SYNTAX: cleantrap <trap>\n");
                     return 1;
                 }
                 target=arg; 
                 
                 ob=present(target, this_player() );
                 
                 if (!ob)
                 {
                     write("You don't seem to have that");
                 }
                 
                 if( ! is_a("/obj/trap/VerminTrap.c",ob)   )
                 {
                     write("You can't clean a " + arg +"\n");
                     return 1;
                 }
                 
                 if(ob->IsFull())
                 {
                     if(this_object()->get_space()>1)
                     {
                         write("You lift the lever on the containment unit with cause a hatch to open. You slide your trap within it and pull the same lever. After a loud whoosing sound the light on the containment unit turns from red to green. Your trap is clean.\n");
                         
                         say(this_player()->query_cap_name() + " cleans their trap\n");
                         ob->setTrapFull(0);
                         //this_object()->set_ghosts("slimer",0,0);
                         //space=space-1;
                         tell_room(environment(this_player()), "A female sounding voice says \"Thank you for keeping our city clean.  " + ob->get_vermin_value() + " dollars have been added to your account.\n");
                         tempCash = this_player()->get_cash();
                         this_player()->setcash(tempCash + ob->get_vermin_value());
                         return 1;
                     }
                     else
                     {
                         write("The containment unit is full!");
                         return 1;
                     }
                     
                 }
                 else
                 {
                     write("That trap is clean!\n");
                     return 1;
                 }
                 
             }