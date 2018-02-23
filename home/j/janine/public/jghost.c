inherit NPC;


/*
Forword-

This file will one day be the one and only file we need to make ALL of our
ghosts. It will take what is passed to it
from the job daemon(JOBS_D) and build a ghost that is needed to complete the
job. Right now it will only make a "Slimer".
This will of course change as I get more into what each GhostClass will be.

-Critical
*/



/*Function Prototypes*/
int GetGhostPower();
void SetGhostPower(int _ghostPower);
int GetGhostClass();
void SetGhostClass(int _ghostClass);
int IsGhost();
int IsCaptured();
int GetFrequency();
int GetFrequencyRange();
int GetFrequencyRangeOffset();
void SetFrequencyRange( int _frequencyRange );
void SetFrequencyRangeOffset( int _frequencyRangeOffset );
void ChooseRandomFrequencyInBounds();
void SetCaptured( object ob );
void Release( object ob );
void BreakFree();
int GetGhostID();
void SetGhostID(int id);
string GetGhostLong();
void SetGhostLong( string long );
string GetGhostShort();
void SetGhostShort( string short );
string GetGhostName();
void SetGhostName( string name );
void BreakFreeHeartBeat();

/*The AI function */
void MakeChoice();
int CanAttack();
int CanMove();
void Attack( object *Targets );

/* Global Variables */
int frequency;
int frequencyRange;
int frequencyRangeOffset;
int timeToBreakFree = 2;
int timeToBreakFreeDefault = 2;
int ghostPower;
int ghostClass;
int ghostID;
object *linkedBusters;
int InCombat;

nosave int rand;

void setup()
{
    set_name("slimer");
    set_short("A powerful slimer floats in the room");
    set_long("A floating green blob, its ectoplasm is heavily wrinkled\n" +  
             "and its mouth takes up most of its 'face'.\n" + 
             "It has two stubby arms and a massive red tongue.\n");

    set_id( ({"slimer", "ghost", "Slimer", "Ghost"}) );    
say ("in jghost.c");
    set_heart_beat(5);
}

/**
 * Function to determine if this is a ghost
 */

int GetGhostPower()
{
say ("in jghost.c");
    return ghostPower;
}

void SetGhostPower( int _ghostPower )
{
    ghostPower = _ghostPower;
}


int IsGhost()
{
    return 1;
}

int IsCaptured()
{
    return linkedBusters && sizeof( linkedBusters ) > 0;
}

/**
 * returns the ghost's frequency
 */
int GetFrequency()
{
   return frequency;
}

/**
 * returns the frequency range
 */
int GetFrequencyRange()
{
    return frequencyRange;
}

/**
 * Returns the Range offset.
 */
int GetFrequencyRangeOffset()
{
    return frequencyRangeOffset;
}

/**
 * returns the frequency range
 */
void SetFrequencyRange( int _frequencyRange )
{
    frequencyRange = _frequencyRange;
}

/**
 * Returns the Range offset.
 */
void SetFrequencyRangeOffset( int _frequencyRangeOffset )
{
    frequencyRangeOffset = _frequencyRangeOffset;
}

/**
 * Chooses the frequency for this ghost based off the frequency range and
 * offset
 */
void ChooseRandomFrequencyInBounds()
{
    frequency = random( GetFrequencyRange() ) + GetFrequencyRangeOffset() + 1;
}

void SetCaptured( object ob )
{
    if( linkedBusters == 0 )
    {
        linkedBusters = allocate( 0 );
    }

    if( sizeof( linkedBusters == 0 ) )
    {
        timeToBreakFree = timeToBreakFreeDefault;
    }

    if( member_array( ob, linkedBusters ) == -1 )
    {
        linkedBusters += ({ ob });
    }
} 

void Release( object ob )
{
    linkedBusters -= ({ ob });
}

void heart_beat()
{
    MakeChoice();
    BreakFreeHeartBeat();
    
}

void BreakFreeHeartBeat()
{


	say("Ghost's Checked if it was captured\n");
	say(linkedBusters);
    if( sizeof( linkedBusters ) <=0 )
    {
        return;
    }

    timeToBreakFree--;
    if( timeToBreakFree == 0 )
    {
        BreakFree();
    }
}

void BreakFree()
{
    int breakFreeRoll;
    int roll;
    int testDC;

say("Ghost trying to break free\n");

    timeToBreakFree = timeToBreakFreeDefault;

    
    roll = random( 100 ) + 1;

    breakFreeRoll += roll;
    while( roll == 100 && breakFreeRoll < 1000 )
    {
        breakFreeRoll += roll;
        roll = random( 100 ) + 1;
    }

    testDC = sizeof( linkedBusters ) * 10 + 100 - (ghostPower*4);

    tell_room( environment( this_object() ), "ROLLING: 1d100(" + breakFreeRoll +
") vs " + testDC + "\n" );

    if( breakFreeRoll > testDC )
    {
        //set_heart_beat( 0 );
        ChooseRandomFrequencyInBounds();
        for( int i = 0; i < sizeof( linkedBusters ); i++ )
        {
            linkedBusters[i]->SetCombatBusy( 0 );
        }
        linkedBusters = allocate( 0 );
        tell_room( environment( this_object() ), sprintf( "The %s struggles and
with a burst of supernatural force throws the contianment beams and is free!\n",
query_cap_name() ) );
    }
    else
    {
       tell_room( environment( this_object() ), sprintf( "The %s struggles but
cannot break free.\n", query_cap_name() ) );
    }
}

/* Ghost IDs are how we know players have the Ghosts they need for Jobs */

int GetGhostID()
{
     return ghostID;
}

void SetGhostID(int id)
{
    ghostID =id;
}

/* Ghost Class is how we setup our Slimers/Poltergists/Specters and the likes

Ghost Classes are as follows

Slimer        = 0
Poltergists   = 1
Specters      = 2
Skin Stealers = 3
Banhsees      = 4

Remember this will change the look and powers of the ghost.


*/

int GetGhostClass ()
{
     return ghostClass;
}

void SetGhostClass ( int _ghostClass )
{
     ghostClass = _ghostClass;
}


/* These functions will change the Long, Short, Name of the ghost based on how
the GhostClass is set. */


string GetGhostLong()
{
     this_object()->query_long();
}

void SetGhostLong( string long )
{
     this_object()->set_long(long);
}


string GetGhostShort()
{
     this_object()->query_short();
}


void SetGhostShort( string short )
{
     this_object()->set_short(short);
}

string GetGhostName()
{
     this_object()->query_name();
}

void SetGhostName( string name )
{
     this_object()->set_name(name);
}

void SetGhostIDs( array IDs )
{
     this_object()->set_id( IDs );
}


int CanAttack()
{
    return sizeof( linkedBusters ) <= 0;
}

int CanMove()
{
    return sizeof( linkedBusters ) <= 0;
}


void MakeChoice()
{
    object *roominv;
    object *targets;
    array exits;

    roominv = allocate( 0 );
    targets = allocate( 0 );

    roominv = all_inventory( environment( this_object() ) );

	say(roominv);

    for( int i = 0; i < sizeof( roominv ); i++ )
    {
        if( is_a (PLAYER, roominv[ i ] ) && !wizardp( roominv[ i ] ) )
        {
            targets += ({ roominv[ i ] });
        }
    }

	say("Ghost picking Targets. Valid Targets it sees are:");
	say(targets);
	say ("\n");


    if( sizeof (targets ) > 0 && CanAttack() )
    {
        Attack(targets);
    }
    else if( CanMove() )
    {
        exits = keys( environment( this_object() )->query_exits() );    
        command( exits[ random( sizeof( exits ) ) ] );
    }
}

void Attack( object *Targets )
{
    string *Attacks;
    object Target;

    if( sizeof( Targets ) <= 0 )
    {
        return;
    }

    Attacks = allocate( 0 );

    Attacks += ({ "Trip" });
    Attacks += ({ "Blast" });
    Attacks += ({ "Slime" });

    Target = Targets[random( sizeof( Targets ) )];

    foreach( string attack in Attacks )
    {
        if( Target && call_other( this_object(), "Should" + attack + "Attack",
Target ) )
        {
            call_other( this_object(), "Do" + attack + "Attack", Target );
            return;
        }
    }
}

int ShouldTripAttack( object Target )
{
    return random( 2 );
}

void DoTripAttack( object Target )
{
    object HitData;
    int Damage;
    string AttackName;

    HitData = clone_object( "/std/combat/HitData.c" );

    AttackName = "Trip";
    Damage = random( 15 ) + 1;
    
    HitData->SetAttackName( AttackName );
    HitData->SetDamage( Damage );
    HitData->AddStatusEffect( "Knockdown", "You have been knocked down.", ({})
);

    if( !Target->ApplyHit( HitData ) )
    {
        destruct( HitData );
        say( "Attacks something it can't\n" );
        return;
    }

    say( sprintf( "%s trips %s dropping them to the ground! \n",
query_cap_name(), Target->query_cap_name( ) ) );
}

int ShouldBlastAttack( object Target )
{
    return random( 10 ) < 2;
}

void DoBlastAttack( object Target )
{
    object HitData;
    int Damage;
    string AttackName;

    HitData = clone_object( "/std/combat/HitData.c" );

    AttackName = "Blast";
    Damage = random( 20 ) + 1;
    
    HitData->SetAttackName( AttackName );
    HitData->SetDamage( Damage );

    if( !Target->ApplyHit( HitData ) )
    {
        destruct( HitData );
        say( "Attacks something it can't\n" );
        return;
    }

    say( sprintf( "%s blasts %s causing them a bit of pain! \n",
query_cap_name(), Target->query_cap_name() ) );
}

int ShouldSlimeAttack( object Target )
{
    return 1;
}

void DoSlimeAttack( object Target )
{
    object HitData;
    int Damage;
    string AttackName;

    HitData = clone_object( "/std/combat/HitData.c" );

    AttackName = "Slime";
    Damage = 0;
    
    HitData->SetAttackName( AttackName );
    HitData->SetDamage( Damage );
    HitData->AddStatusEffect( "Slimed", "You have been slimed.", ({}) );
    HitData->AddStatusEffect( "Knockdown", "You have been knocked down.", ({})
);

    if( !Target->ApplyHit( HitData ) )
    {
        destruct( HitData );
        say( "Attacks something it can't\n" );
        return;
    }

    say( sprintf( "%s slimes %s landing them on the ground covered in goo! \n",
query_cap_name(), Target->query_cap_name() ) );
}
