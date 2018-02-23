inherit COMMAND;

int main(string arg)
{
	 object player=this_player();
	 

	 write("Health: %^NORMAL%^RED%^" +player->get_health() +"%^RESET%^\n");
	 write("Statuses: \n");
	 
	if(player->CheckForStatus("slimed"))
		write("Your covered in slime.\n");
	if(player->CheckForStatus("knockdown"))
		write("Your knocked down.\n");
	if(player->CheckForStatus("broken_arm"))
		write("Your arm is broken\n");
	if(player->CheckForStatus("broken_leg"))
		write("Your leg is broken\n");
	if(player->CheckForStatus("scared"))
		write("Your scared witless\n");
     return 1;
	 
}

