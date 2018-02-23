//List command for shops.

inherit COMMAND;


int main(string arg)
{
     string target;
     string output;
     int cost;
     object *inventory;
     object shopkeeper;
     object *room;
     
     if(strlen(arg)==0)
     {
         room=all_inventory(environment(this_player()));
         for(int i=0; i<sizeof(room);i++)
         {
              if(room[i]->isShop())
              {
              shopkeeper=room[i];
              inventory=all_inventory(shopkeeper);
              output="Shopkeeper:" + shopkeeper->query_cap_name() + "\n";
              output+="#   Item                                      Cost\n";
              output+="==================================================\n";
              for(int a=0; a<sizeof(inventory);a++)
              {
                   cost=inventory[a]->getValue();
                   output += sprintf("%2d) %-35.35s %10.10s\n", a+1, inventory[a]->query_short(), sprintf( "$%d.%2.2d", cost/100, cost%100 ));
                  
                   
              }
             
              output +="==================================================\n";
              write(output);
              }

         }

         
     }
     else
     {    
	     sscanf(arg,"%s",target); 
         shopkeeper = present( target, environment( this_user() ) );
         if(shopkeeper->isShop())
         {
              inventory=all_inventory(shopkeeper);
              output="#   Item                                      Cost\n";
              output+="==================================================\n";
              for(int i=0; i<sizeof(all_inventory(shopkeeper));i++)
              {
                   if(inventory[i]->getValue()==0)
                   {
                        cost=0;
                   }
                   else
                   {
                        cost=inventory[i]->getValue()/100;
                   }
                   output += sprintf("%2d) %-25.25s $%10d\n", i+1, inventory[i]->query_short(), cost);
                  
                   
              }
             
              output +="==================================================\n";
              write(output);
         }
         
     }
 


     return 1;
}

string help()
{
    return
    HIW + " SYNTAX:" + NOR + " list <shopkeeper>\n\n" +
    "Used to check the inventory of a shop keeper\n";
}
