/* shopkeep.c

 Criticalfault @ GBmud
 15-JUNE-09
 Base Shopkeeper class

 Modified:

 Emraef @ GBmud | 15-JUNE-09
   -Moved to new location
   -changed inheritance to NPC 
   -changed file name to shopkeep.c
*/

inherit NPC;


/*function prototypes */
int isShop();
array getIventory();
int getBankRoll();
void setBankRoll( int cash );


/* Gobal Variables */
int bankroll;
array inventory;


int isShop()
{
	return 1;
}

array getInventory()
{
     return all_inventory(this_user());
}

int getBankRoll()
{
    return bankroll;
}

void setBankRoll( int cash )
{
    bankroll=cash;
}
