/* HitData.c
 *
 * Emraef @ GBmud
 * 10-AUG-09
 * Base GB Hit Data
 *
 */

/***
 * Instance Variables
 ***/

// Name of the attack
string attackName;

// Status Effects
mixed *statusEffects;

string *descriptors;

string suggestedDefense;
int defenseDifficulty;

int damage;

object attacker;
object victim;

object weapon;

int attackType;

string hitText;
string missText;


string toString()
{
    string retString;

    retString = sprintf( "[AttackName: %s | ", attackName );

    foreach( mixed *SE in statusEffects )
    {
        retString += sprintf( "%s", SE[0] );
    }

    return retString;
}


/**
 * Called by the driver when this object is created
 */
void create()
{
    damage = 0;
    statusEffects = allocate( 0 );
    descriptors = allocate( 0 );

    suggestedDefense="dodge";
    defenseDifficulty=0;
    attackType = 0;
    hitText = "[HIT] ChangeMe";
    missText = "[MISS] ChangeMe";
}

/**
 * Sets this Hit Data's damage value
 *
 * @param[in] _damage - new damage value
 */
void SetDamage( int _damage )
{
    damage = _damage;
}

/**
 * Gets this Hit Data's damage Value
 *
 * @return int - damage
 */
int GetDamage()
{
    return damage;
}

/**
 * Sets the attacker
 *
 * @param[in] _attacker - the attacker for this hit data
 */
void SetAttacker( object _attacker )
{
    attacker = _attacker;
}

/**
 * Gets the attacker for this hitdata
 *
 * @return object - the attacker
 */
object GetAttacker()
{
    return attacker;
}

/**
 * Sets the victim
 *
 * @param[in] _victim - the victim for this hit data
 */
void SetVictim( object _victim )
{
    victim = _victim;
}

/**
 * Gets the victim for this hitdata
 *
 * @return object - the victim
 */
object GetVictim()
{
    return victim;
}

/**
 * Sets the weapon
 *
 * @param[in] _weapon - the weapon for this hit data
 */
void SetWeapon( object _weapon )
{
    weapon = _weapon;
}

/**
 * Gets the weapon for this hitdata
 *
 * @return object - the weapon
 */
object GetWeapon()
{
    return weapon;
}

/**
 * Set Attack name
 *
 * @param[in] Attack Name
 */
void SetAttackName( string _AttackName )
{
    attackName = lower_case( _AttackName );
}

/**
 * Gets this hit data's Attack Name
 *
 * @return string - attackName
 */
string GetAttackName()
{
    return attackName;
}


/**
 * Set Attack name
 *
 * @param[in] Attack Name
 */
void AddStatusEffect( string _Id, string _Short, mixed *_Data )
{
    _Id = lower_case( _Id );

    statusEffects += ({ ({ _Id, _Short, _Data }) });
}

/**
 * Gets this hit data's Attack Name
 *
 * @return string - attackName
 */
mixed *GetStatusEffects()
{
    return statusEffects;
}


/**
 * Adds a descriptor tag to the descriptor list
 *
 * @param[in] Descriptor name
 */
void AddDescriptor( string _descriptor )
{
    descriptors += ({ lower_case( _descriptor ) });
}

/**
 * Returns if a descriptor is in the descriptor list
 *
 * @param[in] _descriptor - the descriptor to test for
 *
 * @return int - 0 for failed to find non zero for found
 */
int HasDescriptor( string _descriptor )
{
    return -1 != member_array( _descriptor, descriptors );
}

/**
 * Sets the suggested defense of the attack
 *
 * @param[in] _defense - the defense to set the suggested defense to
 */
void SetDefense( string _defense )
{
    suggestedDefense = _defense;
}

/**
 * returns the suggested defense
 *
 * @return string - suggestedDefense
 */
string GetSuggestedDefense()
{
    return suggestedDefense;
}

/**
 * Sets the defense difficulty
 *
 * @para[in] _diff the difficulty of the defense roll
 */
void SetDefenseDifficulty( int _diff )
{
    defenseDifficulty = _diff;
}

/**
 * Returns the defense diff
 *
 * @return - defenseDifficulty
 */
int GetDefenseDifficulty()
{
    return defenseDifficulty;
}

int GetAttackType() { return attackType; }
string GetHitText() { return hitText; }
string GetMissText() { return missText; }

void SetAttackType( int _attackType ) { attackType = _attackType; }
void SetHitText( string _hitText ) { hitText = _hitText; }
void SetMissText( string _missText ) { missText = _missText; }
