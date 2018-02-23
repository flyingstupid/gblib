inherit COMMAND;
int main (string arg)
{
	//string target;
	//string action;
	object player;
	//object victim;
	object *room;
	string temp;

	player=this_player();
	temp = player->query_cap_name();
	printf(temp);

	room = all_inventory( environment( this_player() ) );
	for( int i = 0; i < sizeof( room ); i++ )
        {
		if( is_a (PLAYER, room[ i ] ))
		printf(room[ i ]->query_cap_name());
	}

	return 1;
}
