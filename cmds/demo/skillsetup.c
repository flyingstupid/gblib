inherit COMMAND;

int main(string arg)
{

	object player;

	player=this_player();
	
	write("Setting starting skills...\n");
	
	player->set_skill("aim",50);
	player->set_skill("throw",50);
	player->set_skill("scan",50);
	player->set_skill("dodge",50);
	player->set_skill("firstaid",50);
	player->set_skill("roll",50);
	player->set_skill("block",50);

	write("Player Ready for Action!\n");
	return 1;
}
