/* object.c
 *
 * Tacitus
 * Grouped on October 22nd, 2005
 */

string get_base(mixed ob)
{
    string temp;

    if (stringp(ob)) return ob;

    sscanf(file_name(ob), "%s#%*s", temp);

    if (!temp) temp = file_name(ob);

    return temp;
}

int getoid(object ob)
{
	int id;

	sscanf(file_name(ob || previous_object()), "%*s#%d", id);
	return id;
}

object find_object( string str )
{
    if( !str )
    {
        return 0;
    }

    return efun::find_object( str );
}

object load_object_safe( string str )
{
    if( !str )
    {
        return 0;
    }

    return efun::load_object( str );
}

int is_a( string path, object ob )
{
    if( path[<2..] == ".c" )
    {
        path = path[0..<3];
    }

    if( get_base( ob ) == path )
    {
        return 1;
    }

    return inherits( path, ob );
}


object *all_inventory( object ob )
{
    object array returnArray;

    if( ob )
    {
        returnArray = ob->get_inventory( this_user() );
    }

    if( !returnArray && ob )
    {
        return efun::all_inventory( ob );
    }

    return returnArray;
}

object *_all_inventory( object ob )
{
    return efun::all_inventory( ob );
}
