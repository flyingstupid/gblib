inherit GHOST;

void setup()
{
    set_name( "specter" );
    set_short( "A specter floats in the room." );
    set_long("A floating shimmering humanesque shape floats here.  It warps the things\n" +
             "behind it strangly as it moves bobbimg and waving\n" );

    set_id( ({ "ghost", "spook", "speck", "specter", "spec" }) );
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

    Attacks += ({ "Blast" });

    Target = Targets[random( sizeof( Targets ) )];

    foreach( string attack in Attacks )
    {
        if( Target && call_other( this_object(), "Should" + attack + "Attack",Target ) )
        {
            call_other( this_object(), "Do" + attack + "Attack", Target );
            return;
        }
    }
}

int ShouldBlastAttack( object Target )
{
    return 1;
}
