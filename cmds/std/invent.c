inherit COMMAND;

int InventList();
int InventCreate(string cmdArg);
int InventInfo(string cmdArg);

array *inventDB;

int main ( string arg )
{
	object player;
	object *inv;
	string cmd;
	string cmdArg;

	
	if(!arg)
	{
		write("SYNTAX: invent list, create, info\n");
		return 1;
	}
	
	sscanf(arg,"%s %s",cmd,cmdArg);
	
	player=this_player();
	inv=all_inventory(player);
	
	if(cmd=="list")
	{
		InventList();
	}
	if(cmd=="create")
	{
		InventCreate(cmdArg);	
	}
	if(cmd=="info")
	{
		InventInfo(cmdArg);
	}
	
	return 1;	
}

int InventList()
{
    /*
	string inventString;
	
    inventDB = ({"1","Focusing Crystal","100","R10 I20 RL100"});
	
    inventString = "%^BOLD%^BLACK%^==================================[%^RED%^INVENT%^BLACK%^]====================================%^RESET%^\n\n";
    inventString +=" ID# Description                -COST-      -REQUIREMENT- \n\n";
	//for(int i=0;i<sizeof(inventDB);i++)
	    
    inventString += sprintf(" %-3.3s]  %-25.25s RP%-5.5s    %s",inventDB[0],inventDB[1],inventDB[2],inventDB[3]);
	
	
	inventString +="\n\n  R=Research L=Life Time Total P=Points I=Invention C=Collection\n";
	inventString +="%^BOLD%^BLACK%^==========================================================%^RESET%^\n";
 
	write(inventString);
	
    */
	return 1;	
}

int InventCreate(string cmdArg)
{
    return 1;
}

int InventInfo(string cmdArg)
{
    return 1;	
}

