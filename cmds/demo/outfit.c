inherit COMMAND;

#define SPAWNED_PACK  "/obj/protonpack/protonpack.c"
#define SPAWNED_METER "/obj/pkemeter/pkemeter.c"
#define SPAWNED_TRAP  "/obj/trap/trap.c"
#define SPAWNED_UNIFORM "/obj/armor/jumpsuit.c"

int main( string arg )
{
    object player;
    object pack;
    int hasPack;
    object meter;
    int hasMeter;
    object trap;
    int hasTrap;
	object uniform;
	int hasUniform;
	
    object *inventory;

    player=this_player();

    inventory = all_inventory(player);    
	    
    foreach( object ob in inventory )
    {
        if( is_a( SPAWNED_PACK, ob ) )
        {
            hasPack = 1;
        }
        else if( is_a( SPAWNED_METER, ob ) )
        {
            hasMeter = 1;
        }
        else if( is_a( SPAWNED_TRAP, ob ) )
        {
            hasTrap = 1;
        }
		else if( is_a( SPAWNED_UNIFORM, ob ) )
		{
			hasUniform=1;
		}
    }

    if( hasPack && hasMeter && hasTrap && hasUniform )
    {
        write( "You dont need any equipment\n" );
    }
    else
    {
        write("Adding equipment!\n");
    }

    if( !hasPack )
    {
        pack= clone_object(SPAWNED_PACK);
        pack->move(player);
        write("Protonpack Added!\n");
    }

    if( !hasMeter )
    {
        meter= clone_object(SPAWNED_METER);
        meter->move(player);
        write("PKE Meter Added!\n");
    }

    if( !hasTrap )
    {
        trap= clone_object(SPAWNED_TRAP);
        trap->move(player);
        write("Trap Added!\n");
    }
	if( !hasUniform )
	{
		uniform=clone_object(SPAWNED_UNIFORM);
		uniform->move(player);
		write("Uniform Added!\n");
	}
    return 1;	
}