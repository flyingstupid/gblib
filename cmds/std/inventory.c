//
//   /cmds/std/inventory.c
//


inherit COMMAND;



void write_equipped_items();

int main(string args)
{
    object *inventory;
    object *holding;
    object *armor;
    object *clothing;
    object *equipped;
    object ob;
    int i;
    
    inventory = all_inventory(this_player());
    
    if(sizeof(inventory) < 1)
    {
        write("You are not currently carrying anything.\n");
        notify_fail("You are not currently carrying anything.\n");
        return 1;
    }

    equipped = ({});
    holding = ({});
    armor = ({});
    clothing = ({});

    for( i = 0; i < sizeof(inventory); ++i ) {
        ob = inventory[i];
        if( ob->is_equipped() ) {
            equipped += ({ ob });
        } else {
            if( is_a( "/obj/armor.c", ob ) ){
                armor += ({ ob });
            } else if( is_a( "/obj/clothing.c", ob ) ) {
                clothing += ({ ob });
            } else {
                holding += ({ ob });
            }
        }
    }

    if( sizeof( equipped ) > 0 ) {
        write("Currently Equipped\n");
        write_equipped_items();
    }
   
    inventory = holding;
    if( sizeof( inventory ) == 0 ) {
        write("You are carrying nothing.\n");
        return 1;
    }

    write("You are carrying the following " + (sizeof(inventory) == 1 ? "item:\n" :
                sizeof(inventory) + " items:\n"));

    if( sizeof( armor ) > 0 ) {
        write("ARMOR:\n");
        for(i = 0; i < sizeof(armor); i ++)
        {
            if( armor[i]->query_short() )
                printf(" %s\n", armor[i]->query_short());
            else
                printf(" ERROR: %s\n", file_name(armor[i]) );
        }
    }

    if( sizeof( clothing ) > 0 ) {
        write("CLOTHING:\n");
        for(i = 0; i < sizeof(clothing); i ++)
        {
            if( clothing[i]->query_short() )
                printf(" %s\n", clothing[i]->query_short());
            else
                printf(" ERROR: %s\n", file_name(clothing[i]) );
        }
    }

    if( sizeof( inventory ) > 0 ) {
        write( "OTHER:\n" );
        for(i = 0; i < sizeof(inventory); i ++)
        {
            if( inventory[i]->query_short() )
                printf(" %s\n", inventory[i]->query_short());
            else
                printf(" ERROR: %s\n", file_name(inventory[i]) );
        }
    }
    return 1;
}

int render_slot( string slot )
{
    object player;
    object ob;

    player = this_player();

    if( !player->is_valid_wear_loc( slot ) ) {
        printf( "[%-8.8s] %s\n", slot, "INVALID WEAR LOCATION" );
        return 0;
    }

    ob = player->get_object_in_slot( slot );
    if( ob != 0 ) {
        printf( "[%-8.8s] %s\n", slot, ob->query_short() );
        return 1;
    }

    return 0;
}

void write_equipped_items()
{
    int uniform;
    int group;

    group = 0;

    group += render_slot( "head" );
    group += render_slot( "neck" );
    uniform = render_slot( "uniform" );
    if( !uniform ) { group += render_slot( "body" ); }
    group += render_slot( "r_arm" );
    group += render_slot( "l_arm" );
    group += render_slot( "r_wrist" );
    group += render_slot( "l_wrist" );
    group += render_slot( "r_hand" );
    group += render_slot( "l_hand" );

    group += render_slot( "waist" );
    if( !uniform ) { group += render_slot( "legs" ); }

    group += render_slot( "r_foot" );
    group += render_slot( "l_foot" );

    group += uniform;
    if( group > 0 ) {
        write("\n");
    }

    group = 0;
    group += render_slot( "about" );
    group += render_slot( "back" );
    group += render_slot( "eyes" );
    group += render_slot( "r_ear" );
    group += render_slot( "l_ear" );

    if( group > 0 ) {
        write("\n");
    }

    group = 0;
    group += render_slot( "r_weapon" );
    group += render_slot( "l_weapon" );
}

string help()
{
    return(HIW + " SYNTAX: " + NOR + "inventory\n\n"
           "This command displays a list of everything that is currently\n"
           "in your inventory.\n");
}
