inherit COMMAND;


int main(string arg)
{
    
    
    int cost;
    object *inventory;
    object shopkeeper;
    object *room;
    object player;
    int choice;
    object item;
    object item2;

    player=this_player();
    if(sscanf(arg,"%d",choice)>1)
    {
         write("SYNTAX: buy <number>\n");
         return 1;
         
    }
    else
    {
         
         room=all_inventory(environment(this_player()));
         for(int i=0; i<sizeof(room);i++)
         {
              if(room[i]->isShop())
              {
                   
                   shopkeeper=room[i];
             
                   inventory=all_inventory(shopkeeper);
                   
              }

         }
        

         

    }
    
    if(choice>sizeof(inventory) || choice==0 || choice<0)
    {
         write("I suggest an item they have.\n");
         return 1;     
    }
    else
    {
         item=inventory[choice-1];
         cost=item->getValue();
         if(player->get_cash()<cost)
         {
              write("You can't afford that item!\n");
         }
         else
         {
              player->set_cash(player->get_cash()-cost);
              write("You purchase " + item->query_short()+ " for $"+ cost +". \n");
              item2 = clone_object(get_base(item));
              item2->move(player);
         }
          
         
    }       
          
    


     
    
    return 1;
}


string help()
{
    return
    HIW + " SYNTAX:" + NOR + " buy <number>\n\n" +
    "Used to buy items from shopkeepers\n";
}
