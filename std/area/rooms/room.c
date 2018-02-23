/*
 /std/area/rooms/room.c
 Tacitus@TLPUniversity
 Standard room inheritable
 * Special thanks to Icoz@LPUniversity
 */

// Last edited by Tacitus on May 3rd, 2006

#include <config.h>

inherit OBJECT;

mapping exits = ([]), items = ([]);
mapping ghostExits = ([]);
int light = 1;
int ghost = 1;
string *tossables = ({"food","drink","rock"});
mapping oppexits = ([ "north":"south",
                     "south":"north",
                     "east":"west",
                     "west":"east",
                     "northwest":"northeast",
                     "northeast":"northwest",
                     "southeast":"southwest",
                     "southwest":"southeast" ]);

int set_exits(mapping exit);
int remove_exit(string id);
int add_exit(string id, string path, int DoorState, string keyPath );
int set_light(int level);
int set_items(mapping itemData);
int remove_item(string id);
int add_item(mixed id, string desc);
int valid_exit(string exit);
int query_light();
int setup();
int query_roomType();
string query_short();
string query_long();
string query_item(string id);
string query_exit(string id);
mapping query_items();
mapping query_exits();
void write_to_room( string str,object array exc );
mapping query_ghostExits();

// Anti Ghost Room Stuffs
void set_ghost_ok(int ghost);
int get_ghost_ok();

// Tossing objects for Poltergist powers
void *set_tossables( string *newtossables);
string *get_tossables();
string get_onetoss();

// Hurlable objects
object find_hurlable();


void create()
{
    setup();
}

int setup()
{
    return 1;
}

int query_roomType()
{
    return 1;
}

int set_exits(mapping exit)
{
    exits = exit;
    set("exits", exit);
    return 1;
}

mapping query_exits()
{
    mapping copy;
    copy = exits;
    return copy;
}

int set_ghostExits(mapping exit)
{
    ghostExits = exit;
    set("ghostExits", exit);
    return 1;
}

mapping query_ghostExits()
{
    mapping copy;
    copy = ghostExits;
    return copy;
}

string query_exit(string id)
{
    if(sizeof(exits) < 1)
    {
        return 0;
    }
    
    if(exits[id])
    {
        if( stringp( exits[id] ) )
        {
            return exits[id];
        }
        else if( arrayp( exits[id] ) )
        {
            return exits[id][0];
        }
    }
    
    return 0;
}

string query_ghostExit(string id)
{
    if(sizeof(ghostExits) < 1)
    {
        return 0;
    }
    
    
    if(ghostExits[id])
    {
        if( stringp( ghostExits[id] ) )
        {
            return ghostExits[id];
        }
        else if( arrayp( ghostExits[id] ) )
        {
            return ghostExits[id][0];
        }
    }
}

string query_ghostExitString( string id )
{
    if(sizeof(ghostExits) < 1)
    {
        return "";
    }
    
    if(ghostExits[id])
    {
        if( stringp( ghostExits[id] ) )
        {
            return "goes" + id + ".";
        }
        else if( arrayp( ghostExits[id] ) )
        {
            return ghostExits[id][1];
        }
    }
    
    return "";
}

string query_ghostEnterString( string id )
{
    if(sizeof(ghostExits) < 1)
    {
        return "";
    }
    
    if(ghostExits[id])
    {
        if( stringp( ghostExits[id] ) )
        {
            return "enters.";
        }
        else if( arrayp( ghostExits[id] ) )
        {
            return ghostExits[id][2];
        }
    }
    
    return "";
}

int query_door_state( string id )
{
    if(sizeof(exits) < 1)
    {
        return 0;
    }
    
    if(exits[id])
    {
        if( arrayp( exits[id] ) && sizeof( exits[id] ) > 1 )
        {
            return exits[id][1];
        }
    }
    
    return 0;
}

void set_door_state( string id, int state )
{
    object otherRoom;
    int otherRoomState;
    if(exits[id] && arrayp( exits[id] ) && sizeof( exits[id] ) > 1 )
    {
        exits[id][1] = state;
        otherRoom = load_object_safe( query_exit( id ) ); 
        
        if( otherRoom && oppexits[id] )
        {
            otherRoomState = otherRoom->query_door_state( oppexits[id] );
            
            if( otherRoomState > 0 && otherRoomState != state )
            {
                otherRoom->set_door_state( oppexits[id], state ); 
            }
        }
        
    }
}

int check_door_key( string id, object key )
{
    if( !exits[id] )
    {
        return 0;
    }
    
    if( !arrayp( exits[id] ) || sizeof( exits[id] ) < 3 )
    {
        return 0;
    }
    
    if( exits[id][2] == "" )
    {
        return 1;
    }
    
    if( !key )
    {
        return 0;
    }
    
    return is_a( exits[id][2], key );
}

int valid_exit(string exit)
{
    if(sizeof(exits) < 1)
    {
        return 0;
    }
    
    if(exits[exit])
    {
        return 1;
    }
    
    return 0;
}

int valid_ghostExit(string exit)
{
    if(sizeof(ghostExits) < 1)
    {
        return 0;
    }
    
    if(ghostExits[exit])
    {
        return 1;
    }
    
    return 0;
}

int remove_exit(string id)
{
    if(sizeof(exits) < 1)
    {
        return 0;
    }
    
    if(!exits[id])
    {
        return 1;
    }
    else 
    {
        map_delete(exits, id);
    }
    
    set("exits", exits);
    
    return 1;
}

int add_exit(string id, string path, int DoorState, string keyPath )
{
    if(exits[id])
    {
        map_delete(exits, id);
    }
    
    if( undefinedp( DoorState ) )
    {
        DoorState = 0;
    }
    
    exits += ([id : ({ path, DoorState, keyPath }) ]);
    set("exits", exits);
    return 1;
}

int remove_ghostExit(string id)
{
    if(sizeof(ghostExits) < 1)
    {
        return 0;
    }
    
    if(!ghostExits[id])
    {
        return 1;
    }
    else 
    {
        map_delete(ghostExits, id);
    }
    
    set("ghostExits", ghostExits);
    
    return 1;
}

int add_ghostExit(string id, string path, string exitString, string enterString )
{
    if(ghostExits[id])
    {
        map_delete(ghostExits, id);
    }
    
    ghostExits += ([id : ({ path, exitString, enterString }) ]);
    set("ghostExits", ghostExits);
    return 1;
}
int set_items(mapping itemData)
{
    mixed id;
    string key;
    mapping item = ([]);
    
    foreach(id, key in itemData)
    {
        if(arrayp(id))
        {
            int i;
            for(i = 0; i < sizeof(id); i++)
            {
                item += ([id[i] : key]);
            }
        }
        else 
        {
            item += ([id : key]);
        }
    }
    
    items = item;
    set("items", item);
    return 1;
}

mapping query_items()
{
    mapping copy;
    copy = items;
    return copy;
}

string query_item(string id)
{
    if(items[id])
    {
        if(items[id][0..1] == "@@") 
        {
            return( call_other(this_object(), items[id][2..(strlen(items[id])-1)]));
        }
        else 
        {
            return items[id];
        }
    }
}


int remove_item(string id)
{
    if(!items[id]) return 1;
    map_delete(items, id);
    set("items", items);
    return 1;
}

int add_item(mixed id, string desc)
{
    
    if(arrayp(id))
    {
        int i;
        
        for(i = 0; i < sizeof(id); i++)
        {
                if(items[id[i]]) map_delete(items, id);
                items += ([id[i] : desc]);
        }
        set("items", items);
    }
    else
    {
        if(items[id]) map_delete(items, id);
        items += ([id : desc]);
        set("items", items);
    }
    return 1;
}

int set_light(int level)
{
    light = level;
    set("light", level);
    return 1;
}

int query_light()
{
    if(!light) return query("light");
    return light;
}

string query_short()
{
    if(::query_short()) return ::query_short();
    else return query("short");
}

string query_long()
{
    if(::query_long()) return ::query_long();
    else return query("long");
}

int receive_object(object ob)
{
    return 1;
}

int release_object(object ob)
{
    return 1;
}

int moveAllowed( mixed dest )
{
    return 0;
}

void write_to_room( string str, object array exc )
{
    foreach( object ob in all_inventory( this_object() ) )
    {
        if( member_array( ob, exc ) != -1 )
        {
            continue;
        }
        
        tell_object( ob, str );
    }
}
/* sets rooms to not allow ghosts to enter*/
/* defaut is 1 meaning that the room is ok for ghosts*/

void set_ghost_ok(int ok){
        ghost = ok;
}

/* determines if rooms are ok for ghosts to enter*/
/* defaut is 1 meaning that the room is ok for ghosts*/
int get_ghost_ok(){
    return ghost;
}

void *set_tossables( string *newtossables)
{	
    tossables=newtossables;	
}


string *get_tossables()
{
    return tossables;
}

string get_onetoss()
{
    return tossables[random(sizeof(tossables))];
}

object find_hurlable()
{
    object *inv;
	
    inv = all_inventory(this_object());	
	
    for(int i=0; i < sizeof(inv);i++)
    {
        if(inv[i]->IsHurlAble())
        {
            return inv[i];
        }
    }
}
