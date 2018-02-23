inherit ROOM;

#define MAX_X 2
#define MAX_Y 2
#define MAX_Z 0

#define ROOM_LINE_SIZE 7
#define RENDER_LIVING 1
#define RENDER_PLAYERS 1
#define RENDER_USER 1

array street;
mapping streetnames;
mapping buildingnames;

int valid_move( int x1, int y1, int z1, int x2, int y2, int z2 );
object *get_inventory( object ob );
object *get_inventory_at_location( int x, int y, int z );
int valid_exit( string exit );

void create()
{
    ::create();
    street = ({ ({ ({ "R1", "R2", "R5", "B1" }), ({ "R2" }), ({ "R2", "R3" }), }),
                ({ ({ "R1" }),        ({ "R5" }),      ({ "R3" }),       }),
                ({ ({ "R1", "R4", }), ({ "R4" }), ({ "R3", "R4", "R5" }), }), });

    streetnames = ([ "R1":({"1st Street", "1st ST"}),
                     "R3":({"2st Street", "2st ST"}),
                     "R2":({"Long Avenue", "Long AVE"}),
                     "R4":({"Smith Way", "Smith WAY"}),
                     "R5":({"Dirk Highway", "Dirk HWY"}), 
                  ]);
    
    buildingnames = ([ "B1":({"library", "/areas/library/library00", "The Library" }),
                    ]);
}


mapping query_exits()
{
    mapping ret;
    int x, y, l, i;

    ret = ([]);
    
    if( valid_exit( "north" ) )
    {
        ret += ([ "north":"" ]);
    }

    if( valid_exit( "south" ) )
    {
        ret += ([ "south":"" ]);
    }

    if( valid_exit( "east" ) )
    {
        ret += ([ "east":"" ]);
    }

    if( valid_exit( "west" ) )
    {
        ret += ([ "west":"" ]);
    }

    if( valid_exit( "northeast" ) )
    {
        ret += ([ "northeast":"" ]);
    }

    if( valid_exit( "northwest" ) )
    {
        ret += ([ "northwest":"" ]);
    }

    if( valid_exit( "southwest" ) )
    {
        ret += ([ "southeast":"" ]);
    }

    if( valid_exit( "southeast" ) )
    {
        ret += ([ "southeast":"" ]);
    }

    x = this_user()->X();
    y = this_user()->Y();

    l = sizeof( street[y][x] );
        
    for( i = 0; i < l; i++ )
    {
        if( !undefinedp( buildingnames[street[y][x][i]] ) )
        {
            ret += ([ buildingnames[street[y][x][i]][0] : "" ]);
        }
    }

    return ret;
}


string query_long()
{
    string returnString;
    string *streetKeys = ({});
    string *buildingKeys = ({});
    //string *statusKeys = ({});
    string *addedDesc = ({});

    int x, y, l, i;
    x = this_user()->X();
    y = this_user()->Y();

    returnString = "You are on ";

    l = sizeof( street[y][x] );
        
    for( i = 0; i < l; i++ )
    {
        if( !undefinedp( streetnames[street[y][x][i]] ) )
        {
            streetKeys += ({ street[y][x][i] });
        }
        else if( !undefinedp( buildingnames[street[y][x][i]] ) )
        {
            buildingKeys += ({ street[y][x][i] });
        }
        else
        {
            addedDesc += ({ street[y][x][i] });
        }
    }
   
    // Add the auto street string
    if( sizeof( streetKeys ) > 1 )
    {
        returnString += "the intersection of ";

        for( i = 0; i < sizeof( streetKeys ); i++ )
        {
            if( i == (sizeof( streetKeys ) - 1) )
            {
                returnString += "and " + streetnames[streetKeys[i]][0] + ".";
            }
            else
            {
                returnString += streetnames[streetKeys[i]][0] + ", ";
            }
        }
    }
    else if( sizeof( streetKeys ) == 1 )
    {
        returnString += streetnames[ street[y][x][0] ][0] + ".";
    }

    if( sizeof( buildingKeys ) > 1 )
    {
        returnString += " Entrances to ";
        for( i = 0; i < sizeof( buildingKeys ); i++ )
        {
            if( i == (sizeof( streetKeys ) - 1) )
            {
                returnString += "and " + buildingnames[buildingKeys[i]][2];
            }
            else
            {
                returnString += buildingnames[buildingKeys[i]][2] + ", ";
            }
        }
        returnString += " are just off the street.";
        
    }
    else if( sizeof( buildingKeys ) == 1 )
    {
        returnString += " An entrance to " + buildingnames[buildingKeys[0]][2] + " is just off the street.";
    }
   
    // Add aditional description text
    for( i = 0; i < sizeof( addedDesc ); i++ )
    {
        returnString += " " + addedDesc[i];
    }

    // Auto Wrap
    returnString = auto_wrap( returnString, 60 );

    return returnString + "\n";
}

string *query_street()
{
    return street;
}

string query_short()
{
    string returnString;
    int x, y;
    x = this_user()->X();
    y = this_user()->Y();

    returnString = "";

    for( int i = 0; i < sizeof( street[y][x] ); i++ )
    {
        if( !undefinedp( streetnames[street[y][x][i]] ) )
        {
            if( i != 0 )
            {
                returnString += "+";
            }

            returnString += streetnames[street[y][x][i]][1];
        }
    }

    return returnString;
}

int move_player( object player, string verb, string arg )
{
    int x=0,y=0,z=0,i,l;

    if( !player )
    {
        return 0;
    }

    if( player->has_to_wait( MOVE_WAIT_TIME_TYPE ) )
    {
        return 2;
    } 

    x = player->X();
    y = player->Y();
    z = player->Z();
    
    l = sizeof( street[y][x] );
        
    for( i = 0; i < l; i++ )
    {
        if( !undefinedp( buildingnames[street[y][x][i]] ) &&
            buildingnames[street[y][x][i]][0] == verb )
        {
            return player->move( buildingnames[street[y][x][i]][1] );
        }
    }

    switch( verb )
    {
        case "north":
            y += -1;
        break;
        case "south":
            y += 1;
        break;
        case "east":
            x += 1;
        break;
        case "west":
            x += -1;
        break;
        case "northwest":
            x += -1;
            y += -1;
        break;
        case "northeast":
            x += 1;
            y += -1;
        break;
        case "southwest":
            x += -1;
            y += 1;
        break;
        case "southeast":
            x += 1;
            y += 1;
        break;
        default:
            return 0;
        break;
    }

    if( !valid_move( x, y, z, player->X(), player->Y(), player->Z() ) )
    {
        return 0;
    }

    player->SetLocation( x, y, z );
    player->move( this_object() );

    tell_object( this_user(), sprintf( "Current Location: %d, %d, %d\n", player->X(), player->Y(), player->Z() ) ); 

    return 1;
}

int valid_exit( string exit )
{
    int x=0,y=0,z=0,i,l;
    object player;

    player = this_user();

    if( !player )
    {
        return 0;
    }

    x = player->X();
    y = player->Y();
    z = player->Z();
    
    l = sizeof( street[y][x] );
        
    for( i = 0; i < l; i++ )
    {
        if( !undefinedp( buildingnames[street[y][x][i]] ) &&
            buildingnames[street[y][x][i]][0] == exit )
        {
            return 1;
        }
    }

    switch( exit )
    {
        case "north":
            y += -1;
        break;
        case "south":
            y += 1;
        break;
        case "east":
            x += 1;
        break;
        case "west":
            x += -1;
        break;
        case "northwest":
            x += -1;
            y += -1;
        break;
        case "northeast":
            x += 1;
            y += -1;
        break;
        case "southwest":
            x += -1;
            y += 1;
        break;
        case "southeast":
            x += 1;
            y += 1;
        break;
        default:
            return 0;
        break;
    }
    

    if( !valid_move( x, y, z, player->X(), player->Y(), player->Z() ) )
    {
        return 0;
    }
    return 1;
}


int valid_move( int x1, int y1, int z1, int x2, int y2, int z2 )
{
    string *room1;
    string *room2;

    if( y1 < 0 || y2 < 0 ||
        y1 > MAX_Y || y2 > MAX_Y || 
        x1 < 0 || x2 < 0 ||
        x1 > MAX_X || x2 > MAX_X )
    {
        return 0;
    }

    room1 = street[y1][x1];
    room2 = street[y2][x2];

    for( int i = 0; i < sizeof( room1 ); ++i )
    {
        if( member_array( room1[i], room2 ) != -1 )
        {
            return 1;
        }
    }

    return 0;
}

object *get_inventory( object ob )
{
    if( !ob )
    {
        return 0;
    }

    return get_inventory_at_location( ob->X(), ob->Y(), ob->Z() );
}

object *get_inventory_at_location( int x, int y, int z )
{
    object *returnArray;

    if( undefinedp( x ) ||
        undefinedp( y ) ||
        undefinedp( z ) )
    {
        return 0;
    }

    returnArray = ({});


    foreach( object ob in _all_inventory( this_object() ) )
    {
        if( ob->X() == x &&
            ob->Y() == y &&
            ob->Z() == z )
        {
            returnArray += ({ ob });
        }
    }

    return returnArray;
}


int IsSaveEnabled()
{
    return 0;
}
