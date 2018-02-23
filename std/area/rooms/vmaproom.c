//
// /std/area/rooms/vmaproom.c
//


inherit ROOM_BASE;

#define ROOM_LINE_SIZE 7
#define RENDER_LIVING 1
#define RENDER_PLAYERS 1
#define RENDER_USER 1

// Room renders
string *s_northwest = ({ "/", " ", " ", "6" });
string *s_northeast = ({ "\\", " ", " ", "7" });
string *s_north     = ({ "-----", "     ", "-+ +-", "-+=+-" });
string *s_south     = ({ "-----", "     ", "-+ +-", "-+=+-" });
array  *s_west      = ({ ({ "|", "|", "|", "|", "|" }), 
    ({ " ", " ", " ", " ", " " }),
    ({ "|", "+", " ", "+", "|" }),
    ({ "|", "+", "]", "+", "|" }) });

array  *s_east      = ({ ({ "|", "|", "|", "|", "|" }), 
    ({ " ", " ", " ", " ", " " }),
    ({ "|", "+", " ", "+", "|" }),
    ({ "|", "+", "[", "+", "|" }) });

string *s_southeast = ({ "/", " ", " ", "6" });
string *s_southwest = ({ "\\", " ", " ", "7" });
//                | /-----\/-----\/-----\ |
string tabOver = "                         ";

array *CreateRoomDescData();
string render_exits();
string render_ghost_exits();
string *render_objects();
string *render_mobs();

/** Render Functions */
string *RenderRoom( string exit );
string RenderHeader();
string *RenderMobiles( object room, string *roomRender );
string ApplyColor( string output );
string GetRoomDescLine(array *data);
/********************/

string vmap( string arg )
{
    string *render;
    array * rooms;
    array *roomLong;
    
    roomLong = CreateRoomDescData();
    
    render = allocate( ROOM_LINE_SIZE * 3 );
    rooms = allocate( 9 );
    
    rooms[0] = RenderRoom( "northwest" );
    rooms[1] = RenderRoom( "north" );
    rooms[2] = RenderRoom( "northeast" );
    
    rooms[3] = RenderRoom( "west" );
    rooms[4] = RenderRoom( "here" );
    rooms[5] = RenderRoom( "east" );
    
    rooms[6] = RenderRoom( "southwest" );
    rooms[7] = RenderRoom( "south" );
    rooms[8] = RenderRoom( "southeast" );
    
    
    for( int i = 0; i < 9; i += 3 )
    {
        for( int j = 0; j < ROOM_LINE_SIZE; j++ )
        {
            render[(i/3)*ROOM_LINE_SIZE+j] = ApplyColor( "| " + rooms[i][j] + rooms[i+1][j] +
                                                        rooms[i+2][j] + " |" );
            
            render[(i/3)*ROOM_LINE_SIZE+j] += "  " + GetRoomDescLine( roomLong );
        }
    }
    
    render += ({  "\\-----------------------/  " + GetRoomDescLine( roomLong ) });
    
    while( roomLong[0] < sizeof( roomLong ) )
    {
        render += ({ tabOver + "  " + GetRoomDescLine( roomLong ) });
    }
    
    return sprintf( "%s%s", RenderHeader(), implode( render, "\n" ) );
}

array *CreateRoomDescData()
{
    array *roomLong;
    string ghostExits;
    
    roomLong = allocate( 2 );
    roomLong[0] = 2;
    roomLong[1] = 0;
    roomLong += explode( implode(explode(this_object()->query_long(),"\n")," "), "/FORCE_NEWLINE/"
                        );
    roomLong += ({ "", "", render_exits() });
    
    ghostExits = render_ghost_exits();
    if( sizeof( ghostExits ) > 0 )
    {
        roomLong += ({ "", ghostExits });
    }
    
    roomLong += ({ "", "" });
    roomLong += render_objects();
    roomLong += render_mobs();
    
    for( int l = 2; l < sizeof( roomLong ); l++ )
    {
        roomLong[l] = explode( roomLong[l], " " );
    }
    
    
    return roomLong;
}

string GetRoomDescLine(array *data)
{
    string retVal;
    int i;
    
    retVal = "";
    
    if( sizeof( data ) <= data[0] )
    {
        return NOR;
    }
    
    for( i = data[1]; i < sizeof(data[data[0]]); i++ )
    {
        if( sizeof( clear_color_tags( retVal + data[data[0]][i] ) ) > 48 )
            break;
        
        retVal += data[data[0]][i] + " ";
    }
    
    if( i < sizeof( data[ data[0] ] ) )
    {
        data[1] = i;
    }
    else
    {
        data[0]++;
        data[1]=0;
    }
    
    return retVal + NOR;
}



string ApplyColor( string output )
{
    output = replace_string( output, "1", "%^RED%^U%^RESET%^" );
    output = replace_string( output, "2", "%^RED%^D%^RESET%^" );
    output = replace_string( output, "3", "%^BOLD%^BLUE%^*%^RESET%^" );
    output = replace_string( output, "4", "%^BOLD%^GREEN%^*%^RESET%^" );
    output = replace_string( output, "5", "%^BOLD%^RED%^*%^RESET%^" );
    output = replace_string( output, "6", "%^RED%^/%^RESET%^" );
    output = replace_string( output, "7", "%^RED%^\\%^RESET%^" );
    output = replace_string( output, "+", "%^BOLD%^WHITE%^+%^RESET%^" );
    output = replace_string( output, "=", "%^RED%^=%^RESET%^" );
    output = replace_string( output, "[", "%^RED%^[%^RESET%^" );
    output = replace_string( output, "]", "%^RED%^]%^RESET%^" );
    
    return output;
}

string RenderHeader()
{
    string returnString;
    
    returnString = "";
    
    if( previous_object(1) &&  adminp( previous_object(1) ) )
    {
        returnString += get_base( this_object() + ".c\n" );
    }
    
    returnString += sprintf( "/%|23.23s\\\n", query_short() );
    
    return returnString;
}

string *RenderRoom( string exit )
{
    string *render;
    object room;
    int east, west;
    int northeast, northwest;
    int southeast, southwest;
    int north, south;
    int up, down;
    
    if( exit == "here" )
    {
        room = this_object();
    }
    else
    {
        room = load_object_safe( query_exit( exit ) );
    }
    
    // if the door is closed then we cannot go though it
    if( query_door_state( exit ) > 1 )
    {
        room = 0;
    }
    
    render = allocate( ROOM_LINE_SIZE );
    
    if( room == 0 ) 
    {
        render[0] = "       ";
        render[1] = "       ";
        render[2] = "       ";
        render[3] = "       ";
        render[4] = "       ";
        render[5] = "       ";
        render[6] = "       ";
        return render;
    }
    
    northeast = min( 3, room->valid_exit( "northeast" ) + room->query_door_state( "northeast" ) );
    northwest = min( 3, room->valid_exit( "northwest" ) + room->query_door_state( "northwest" ) );
    north     = min( 3, room->valid_exit( "north" ) + room->query_door_state( "north" ) );
    southeast = min( 3, room->valid_exit( "southeast" ) + room->query_door_state( "southeast" ) );
    southwest = min( 3, room->valid_exit( "southwest" ) + room->query_door_state( "southwest" ) );
    south     = min( 3, room->valid_exit( "south" ) + room->query_door_state( "south" ) );
    east      = min( 3, room->valid_exit( "east" ) + room->query_door_state( "east" ) );
    west      = min( 3, room->valid_exit( "west" ) + room->query_door_state( "west" ) );
    
    render[0] = s_northwest[northwest] + s_north[north] + s_northeast[northeast];
    
    for( int i = 0; i < 5; i++ )
    {
        render[i+1] = s_west[west][i] + "     " + s_east[east][i];
    }
    
    up   = room->valid_exit( "up" );
    down = room->valid_exit( "down" );
    
    if( up )
    {
        render[1][3] = '1';
    }
    
    if( down )
    {
        render[5][3] = '2';
    }
    
    render[6] = s_southwest[southwest] + s_south[south] + s_southeast[southeast];
    
    RenderMobiles( room, render );
    
    if( exit == "here" && RENDER_USER )
    {
        // Render the player
        render[3] = render[3][0..2] + "5" + render[3][4..];
    }
    
    return render;
}


string *RenderMobiles( object room, string *roomRender )
{
    int randrow, randcol;
    object *inv;
    
    if( !room )
    {
        return roomRender;
    }
    
    inv = all_inventory( room );
    for( int i = 0; i < sizeof( inv ); ++i )
    {
        if( inv[i] == this_user() )
        {
            continue;
        }
        
        if( RENDER_PLAYERS && is_a( PLAYER, inv[i] ) )
        {
            randrow = random(5) + 1;
            randcol = random(5) + 1;
            while( ( randrow == 1 || randrow == 3 || randrow == 5 ) && randcol == 3 )
            {
                randcol = random(5) + 1;
            }
            roomRender[randrow][randcol] = '3';
        }
        else if( RENDER_LIVING && is_a( NPC, inv[i] ) )
        {
            randrow = random(5) + 1;
            randcol = random(5) + 1;
            while( ( randrow == 1 || randrow == 3 || randrow == 5 ) && randcol == 3 ||
                  roomRender[randrow][randcol] == '3' )
            {
                randcol = random(5) + 1;
            }
            roomRender[randrow][randcol] = '4';
        }
    }
    
    return roomRender;
}

string render_exits()
{
    string retVal;
    string *exits;
    
    exits = keys(this_object()->query_exits());
    
    switch(sizeof(exits))
    {
        case 0:
        {
            retVal = (CYN + "There are no obvious exits here." + NOR + "");
            break;
        }
        case 1:
        {
            retVal = (CYN + "The only obvious exit is " + HIY + exits[0] + NOR + CYN + "." + NOR +
                      ""); 
            break;
        }
        default:
        {
            retVal = (CYN + 
                      sprintf("The only obvious exits are %s and %s.",
                              HIY + implode(exits[0..<2], NOR + CYN + ", " + HIY) + NOR + CYN,
                              HIY + exits[<1] + NOR + CYN,
                              ) + NOR + ""
                      );
        }
    }
    
    
    return retVal;
}


string render_ghost_exits()
{
    string retVal;
    string *exits;
    
    retVal = "";
    
    if( !wizardp( this_user() ) )
    {
        return retVal;
    }
    
    exits = keys(this_object()->query_ghostExits());
    
    switch(sizeof(exits))
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            retVal += (RED + "The only ghost exit is " + HIG + exits[0] + NOR + RED + "." + NOR +
                       ""); 
            break;
        }
        default:
        {
            retVal += (CYN + 
                       sprintf("The ghost exits are %s and %s.",
                               HIG + implode(exits[0..<2], NOR + RED + ", " + HIG) + NOR + RED,
                               HIG + exits[<1] + NOR + RED,
                               ) + NOR + ""
                       );
        }
    }
    
    return retVal;
}

string * render_objects()
{
    object *objects;
    objects = filter(all_inventory(this_object()), (: !living($1) :));
    
    if(sizeof(objects) > 0)
    {
        return map(objects, 
                   (: capitalize( WHT + ( $1->query_long() ? $1->query_short(): "ERROR: " + file_name($1)
                                         ) + NOR )  :));
    }
    
    return ({});
}

string * render_mobs()
{
    string *users;
    users = filter(all_inventory(this_object()), (: living($1) && $1 != this_player() :));
    
    if(sizeof(users) > 0)
    {
        return map(users, (: CYN + capitalize($1->query_short() + $1->GetPositionPost()) + NOR :));
    }
    
    return ({});
}

string cambridge( string str )
{
    
}

string scramble_word( string str )
{
    
}
