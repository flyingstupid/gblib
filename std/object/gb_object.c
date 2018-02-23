/* gb_object.c
 *
 * Emraef @ GBmud
 * 04-APR-09
 * Base GB Object
 *
 */

inherit BASE_OBJECT;


int getValue();
void setValue( int value );
int X();
int Y();
int Z();

/** Wear functions */
string get_default_wear_loc();
int is_valid_wear_loc( string loc );
int can_be_equipped();
void equipped_to_location( string loc );
void removed_from_slots();
int is_equipped();

/** value of this object */
int value=0;

/** Position Vars */
int _x;
int _y;
int _z;

/** wear vars **/
string *allowedWearLocs;
string equippedLocation;

void create()
{
    ::create();

    allowedWearLocs = ({});

    equippedLocation = "";
}

/**
 * do not drop if equipped
 */
int prevent_drop()
{
    return is_equipped();
}

/**
 * returns if this object is currently equipped
 */
int is_equipped()
{
    return equippedLocation != "";
}

/**
 * call back from the mobile when this is removed by a wear swap
 */
void removed_from_slots()
{
    equippedLocation = "";
}


/**
 * call back from the mobile when this is equipped
 */
void equipped_to_location( string loc )
{
    equippedLocation = loc;
}

/**
 * called to find out of this object can be worn
 */
int can_be_equipped()
{
    if( undefinedp( allowedWearLocs ) ) {
        return 0;
    }

    return sizeof( allowedWearLocs ) > 0;
}

/**
 * called to check a user specified wear loc
 */
int is_valid_wear_loc( string loc )
{
    int i;

    if( undefinedp( allowedWearLocs ) ) {
        return 0;
    }

    for( i = 0; i < sizeof( allowedWearLocs ); ++i ) {
        if( loc == allowedWearLocs[i] ) {
            return 1;
        }
    }

    return 0;
}

/**
 * called to get the default wear location of the item
 */
string get_default_wear_loc()
{
    if( undefinedp( allowedWearLocs ) || sizeof(allowedWearLocs) == 0 ) {
        return "";
    }

    return allowedWearLocs[0];
}

/**
 * returns the value of this object
 *
 * @return int - value
 */
int getValue()
{
    return value;
}

/**
 * Sets the value of this object
 *
 * @param[in] newValue - new value
 */
void setValue( int newValue )
{
    value=newValue;
}

/**
 * returns _x
 *
 * @return int - _x
 */
int X()
{
    return _x;
}

/**
 * returns _y
 *
 * @return int - _y
 */
int Y()
{
    return _y;
}

/**
 * returns _z
 *
 * @return int - _z
 */
int Z()
{
    return _z;
}

/**
 * Sets this object's location
 *
 * @param[in] x - new _x value
 * @param[in] y - new _y value
 * @param[in] z - new _z value
 */
void SetLocation( int x, int y, int z )
{
    if( !undefinedp( x ) )
    {
        _x = x;
    }
    
    if( !undefinedp( y ) )
    {
        _y = y;
    }

    if( !undefinedp( z ) )
    {
        _z = z;
    }
}

/**
 * Called to Apply a hit to this object.
 *
 * This is the main call for combat.  All combat hits should go through
 * this call allowing objects to handle hits differently
 * 
 * @param[in] hitData - the data object for the hit.  This needs to be cleaned
 *                      by this function.
 *
 * @return int - Non zero if the hit was handled.  0 value indicates that the
 *               Hit was not handled and the hit data was not cleaned.
 */
int ApplyHit( object HitData )
{
    // Default objects are not setup to handle hits.
    return 0;
}

