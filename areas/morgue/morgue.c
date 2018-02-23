inherit ROOM;
void create()
{
     set_light(1);
     set_short("The City Morgue");
     set_long(
          "The city morgue. What can we say? Your dead and you\n"
          "belong here. Don't worry though. Someone will find out\n"
          "soon that your not dead. We think\n"
     );

    set_heart_beat( 20 );
}

void heart_beat()
{
    object *obArray;
    object *allUsers;
    
    obArray = all_inventory( this_object() );
    allUsers = users();

    for( int i = 0; i < sizeof( obArray ); i++ )
    {
        if( member_array( obArray[i], allUsers ) != -1 )
        {
	        tell_object( obArray[i], "You moan loudly and the two Medical Examiners seem to take notice.\n");
            tell_object( obArray[i], "Jim says \"We've got another live one Hank!\"\n" );
            tell_object( obArray[i], "Hank says \"Just toss it back out with the others.\"\n" );
            tell_object( obArray[i], "You are picked up and thrown back into the world.\nJim says \"Try not to die again.\"\n" );
            obArray[i]->HealDamage(9);
            obArray[i]->move( "/areas/demo/demo1.c" );
        }
    }
}
