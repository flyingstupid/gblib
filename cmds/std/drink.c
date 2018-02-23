//     Critical & Janine
//     /cmds/std/drink.c 
//     For all your beverage needs.
//     GB Mud
//

inherit COMMAND;

int main(string arg)
{
    //object player;
    object *inv;
    object drink;
    int drinkFill=-1;
    
    drink = present( arg, this_player() );
    
    //player=this_player();
    inv=all_inventory(this_player());
    
    
    if(!arg)
    {
        write("SYNTAX: drink <object>\n");
        return 1;
    }
for(int i=0; i < sizeof( inv ); i++)
{
    //write ("You have a " + inv[i]->query_name() + " in your inventory.\n");
    if((drink) && is_a ("/obj/drink.c", drink) )
    {
        //drink=inv[i];
        drinkFill=drink->get_fill();
        break;
    }
    else
    {
        write("You can't drink that!\n");
        return 1; 
    }
    
}
if(drinkFill==-1)
{
    write("You don't have a drink!\n");
    return 1;
}    
/*    if(drinkFill<=0)
 {
 write("Your drink is empty! You set it aside.\n");
 destruct(drink);
 }*/
else
{
    write(drink->get_selfDrinkMsg() + "\n");
    say(this_user()->query_cap_name() +drink->get_roomDrinkMsg() + "\n");
    drink->set_fill(drink->get_fill()-1);
   // this_user()->SetBladder(this_user()->GetBladder()+1);
    if(drink->get_fill()==0)
    {
        write("You finish your "+ drink->query_short() +" and you set it
aside.\n");
        say  (this_user()->query_cap_name() + " finishes their drink and sets it
aside.\n");
        destruct(drink);
        return 1;
    }
    if(drink->get_fill()==1)
    {
    write("\nYou have a single sip left\n");
    }
    else
    {
    write("\nYou have "+drink->get_fill()+" sips left.\n");
    }
}

return 1;


}


string help()
{
    return(HIW + " SYNTAX:" + NOR + " drink <object>\n\n" +
           "This command will drink an object that is a drink.\n"+
           "Some drinks have special affects.\n");
}
