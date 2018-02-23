//
// /obj/armor.c
//



inherit OBJECT;

/* FUNCTION PROTOTYPES */

void set_base_defense(int value);
int get_base_defense();
/** Enhancement functions **/
void clear_enhancement( string enhancement );
void apply_enhancement( string enhancement );
int check_for_enhancemement( string enhancement);


/* GLOBAL VARIABLES */
int baseDefense;
mapping enhancements;


void create()
{
    set_id(({"armor"}));
    set_short("armor");
    set_long ("a piece of protective clothing");
    set_base_defense (0);
}


void set_base_defense(int value){
    baseDefense = value;
}

int get_base_defense(){
    return baseDefense;
}



/** Enhancement functions **/
void clear_enhancement( string enhancement )
{
    write( "clearing Enhancements\n");
    if( enhancements[ enhancement ]  )
    {
        enhancements[ enhancement] = 0;
        tell_object(this_player(), "Your armor returns to normal\n");
    }
}
void apply_enhancement( string enhancement )
{
    write( "Applying Enhancements\n");
    
    if( enhancements[enhancement] ){
        return;
    }
    else {
        enhancements[enhancement] = 1;
    }
}
int check_for_enhancemement( string enhancement)
{
    if( ( (enhancements[enhancement] ))){
        return 1;
    }
    else {
        return 0;
    }
}
