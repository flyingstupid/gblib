//
// /std/user/gb_player.c
//


inherit "/std/user/gb_mobile.c";

/*Functions Descriptions*/
void SetCorpID( string ID );
string GetCorpID();

/*Character Generation Functions*/
void SetCharGenOK(int num);
int IsCharGenOK();

/*Death Announcements*/
void DeathAnnounce();

/** Bladder Functions */
void SetBladder(int val);
int GetBladder();

/** Skill functions */
void set_skill( string skillName, int skillValue );
mapping get_skills();
int get_skill( string skillName );
int DoSkillRoll(string skill, int diff);

/** training functions */
void setTrainTime1( int trainTime);
int getTrainTime1();
void setTrainTime2( int trainTime);
int getTrainTime2();


void DoSkillXp(string skill, int diff);

/** stat functions */
void set_stat( string statName, int statValue );
int get_stat( string statName );
mapping get_stats();

/** Health functions */
void set_health( int newHealth );
int get_health();
void SetHealth( int newHealth );
int GetHealth();
void CauseDamage( int damageAmount );
void HealDamage( int healAmount );


/** Job functions */
array get_currentJob();
void set_currentJob(array ghostIDs,string jobNPC, int bid);

/** Research functions */
int GetResearchTotal();
void SetResearchCurrent(int current);
void SetResearchTotal(int total);
int GetResearchCurrent();
void SetNumProjects(int change);
int GetNumProjects ();


/** combat functions */
int ApplyHit( object HitData );
void ApplyStatusEffects( string newStatus );
void ApplyHitDamage( int _damage, string _defenseSkill, int _defenseDiff );
void CauseStatus_knockdown();

/** effect functions **/
void ClearStatus( string status );
void ApplyStatusEffects( string newStatus );

/** Enhancement functions **/
void clear_enhancement( string enhancement );
void apply_enhancement( string enhancement );
int check_for_enhancemement( string enhancement);

/** Newbie Job Functions
These are used for the Business Agent in /areas/franchise/franchise8.c Area
newbieJob variable tells if they have job
newbieJobTotal is how many they have finished
NewbieJobTime is how much time is left on the job
 **/
void setNewbieJob(int num);
int getNewbieJob();
void setNewbieJobTotal(int num);
int getNewbieJobTotal();
void setNewbieJobTime(int num);
int getNewbieJobTime();
void checkNewbieJobTime();
 

/***
 * Instance Variables 
 ***/
int playerGenDone;
mapping playerSkills;
mapping playerStats;
int maxHealth;
int health;
array currentJob;
int researchTotal;
int researchCurrent;
string corpID;
int bladder;
int numProjects;
mapping statuses;
mapping enhancements;
object *projects;

/** Newbie Job Variables
These are used for the Business Agent in /areas/franchise/franchise8.c Area
newbieJob variable tells if they have job
newbieJobTotal is how many they have finished
NewbieJobTime is how much time is left on the job
 **/

int newbieJob;
int newbieJobTime;
int newbieJobTotal;

/** training vairiables */
int TrainTime1, TrainTime2;




//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------


/**
 * called from the create of object.c to setup this object
 */
void setup()
{
    ::setup();
    
    // setup variables if they are missing
    if( !maxHealth ) maxHealth = 100;
    if( !health ) health = maxHealth;
    if( !playerSkills ) playerSkills = allocate_mapping( 0 );
    if( !playerSkills ) playerStats = allocate_mapping( 0 );
    if( !corpID ) corpID = "GBA";
    if( !bladder ) bladder = 0;
    statuses = (["knockdown": 0,
                 "slimed": 0]);
    
    enhancements = (["armor_green": 0,
                     "armor_orange": 0,
                     "armor_purple": 0,
                     "armor_gold": 0]);
    set_heart_beat( 1 );
}

/**
 * Sets the corp ID string for this Player
 *
 * @param ID - the new corp ID
 */
void SetCorpID( string ID )
{
    corpID = ID;
}

/**
 * Gets the corp ID string for this Player
 *
 * @return string - the players corp ID
 */
string GetCorpID()
{
    return corpID;
}


/* Setting the Bladder */
void SetBladder(int val)
{
    bladder=val;
}

/* Getting the Bladder */
int GetBladder()
{
    return bladder;
}


/**
 * Set a skill by skillname
 *
 * @param[in] skillName - Key in the mapping where the skill should be set
 * @param[in] skillValue - value the skill should be set to
 */
void set_skill( string skillName, int skillValue )
{
    if( skillValue == 0 )
    {
        if( !undefinedp( playerSkills[skillName] ) )
        {
            map_delete( playerSkills, skillName );
        }
        
        return;
    }
    playerSkills[skillName] = skillValue;
}

int get_skill( string skillName )
{
    if( undefinedp( playerSkills[skillName] ) )
    {
        return 0;
    }
    
    return playerSkills[skillName];
}

mapping get_skills()
{
    mapping a;
    a = playerSkills;
    
    return a;
}

void set_stat( string statName, int statValue )
{
    playerStats[statName] = statValue;
}

int get_stat( string statName )
{
    if( undefinedp( playerStats[statName] ) )
    {
        return 0;
    }
    
    return playerStats[statName];
}

mapping get_stats()
{
    mapping a;
    a = playerStats;
    
    return a;
}


void set_health( int newHealth )
{
    if( newHealth > maxHealth )
    {
        health = maxHealth;
    }
    else if( newHealth < 0 )
    {
        health = 0;
    }
    else
    {
        health = newHealth;
    }
}

int get_health()
{
    return health;
}

void heart_beat()
{
    if( get_health() <= 0 )
    {
        say(this_player()->query_cap_name() + " hits the ground and stops moving.\n");
        write("Everything goes dark and you feel numb....\n\n\n\n\n\n");
        HealDamage(1);
        call_out("DeathAnnounce",10);
        move( "/areas/morgue/morgue.c" );
    }
    checkNewbieJobTime();
    //    if( get_health() < maxHealth )
    //    {
    //        HealDamage( 1 );
    //    }
}

array get_currentJob()
{
    return currentJob;
}

void set_currentJob(array ghostIDs,string jobNPC, int bid)
{
    currentJob=({ghostIDs,jobNPC, bid});
}

int GetResearchTotal()
{
    return researchTotal;   
}

int GetResearchCurrent()
{
    
    return researchCurrent; 
}

void SetResearchTotal(int total)
{
    researchTotal=total;
}

void SetResearchCurrent(int current)
{
    researchCurrent=current;        
}


void SetNumProjects(int change){
    if (undefinedp (numProjects ) ){
        numProjects = 0;
    }
    numProjects = numProjects + change;
}
int GetNumProjects (){
    return numProjects;
}

/**
 * Finds the skill and does a skill test with the given difficulty
 *
 * @param[in] skill - string name of the skill
 * @param[in] diff - difficulty to modify the skill by
 */
int DoSkillRoll(string skill, int diff)
{
    int d100;
    int skillValue;
    int returnValue;
    
    if( undefinedp( diff ) )
    {
        diff=0;
    }
    
    d100=random(100)+1;
    skillValue = get_skill(skill) - diff;
    
    
    returnValue = skillValue-d100;
    
    tell_object(this_object(), "Rolling: [" + skill + "] of "+ get_skill(skill)
                +" @ Difficulty of [" + diff +"]  Roll was: ["+ d100 + "]\n" + "Result:" +
                returnValue + ".\n");
    // On a failure do a skill advance test
    if( d100 > skillValue )
    {
        DoSkillXp(skill, diff);
    }
    
    return returnValue;
}


/**
 * Tests for the advancement of a skill
 *
 * @param[in] skill - the skill to test for advancement
 * @param[in] diff - the difficulty of the skill test
 */
void DoSkillXp(string skill, int diff)
{   
    int skillValue;
    int realskillvalue;
    
    if( undefinedp( diff ) )
        diff = 0;
    
    realskillvalue = get_skill(skill);
    skillValue = get_skill(skill);
    
    skillValue -= diff;
    
    if((random(100)+1) > skillValue && (random(100)+1) > skillValue)
    {
        set_skill(skill, realskillvalue+1); 
     tell_object(this_object(), "%^GREEN%^You believe you've learned something about "
                    + skill + ".%^RESET%^\n");
    }
}

/** training functions*/


void setTrainTime1(int ttime){ 
    TrainTime1 = ttime;
}


int getTrainTime1(){ 
    return TrainTime1;
}

void setTrainTime2(int ttime){ 
    TrainTime2 = ttime;
}


int getTrainTime2(){ 
    return TrainTime2;
}




/**
 * Causes damage to the player.
 *
 * This cannot be used to heal the player any value 0 or less is ignored.
 *
 * @param[in] damageAmount - amount to subtract from the players current health.
 */
void CauseDamage( int damageAmount )
{
    if( undefinedp( damageAmount ) ||
       damageAmount <= 0 )
    {
        return;
    }
    
    set_health( get_health() - damageAmount );
} 

/**
 * Heals the player an amount
 *
 * This cannot be used to damage the player any value 0 or less is ignored.
 *
 * @param[in] healAmount - the amount to heal by
 */
void HealDamage( int healAmount )
{
    if( undefinedp( healAmount ) ||
       healAmount <= 0 )
    {
        return;
    }
    
    set_health( get_health() + healAmount );
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
    if( undefinedp( HitData ) ||
       !is_a( HITDATA, HitData ) )
    {
        return 0;
    }
    
    ApplyHitDamage( HitData->GetDamage(),
                   HitData->GetSuggestedDefense(),
                   HitData->GetDefenseDifficulty() );
    
    ApplyStatusEffects( HitData->GetStatusEffects() );
    
    // our responsibility to clean up the hit Data.
    destruct( HitData );
    
    return 1;
}       


/**
 * Applies hit damage based on the result of a defense skill test
 *
 * @param[in] _damage - the base damage for the hit
 * @param[in] _defenseSkill - the name of the defense skill to use
 * @param[in] _defenseDiff - the difficulty of the dest
 */
void ApplyHitDamage( int _damage, string _defenseSkill, int _defenseDiff )
{
    int skillTestDiff;
    
    skillTestDiff = DoSkillRoll( _defenseSkill, _defenseDiff );
    
    if( skillTestDiff <= 0 )
    {
        return;
    }
    
    _damage *= ceil(skillTestDiff/10.0); 
    
    CauseDamage( _damage );
}


void ApplyStatusEffects( string newStatus )
{

    write( "Applying status Effects");
    
   
    
    if( statuses[newStatus] ){
        return;
    }
    else {
        statuses[newStatus] = 1;
    }
    call_other( this_object(), "CauseStatus_" + newStatus );
    
}


void ClearAllStatuses()
{
    int i, sz;

    for (i = 0, sz = sizeof(statuses); i < sz; i++)
        statuses[i] = 0;
    
    //command ("say all of my statuses have been cleared.\n");
}

void CauseStatus_knockdown()
{
    say( query_cap_name() + " GOT KNOCKED TO THE GROUND!\n" );
    SetPosition( LAY );
}

void CauseStatus_slimed()
{
    say( query_cap_name() + " has been slimed!\n" );
    
}

mapping get_statuses()
{
    return copy(statuses);
}

void ClearStatus( string status )
{
    
    if( statuses[ status ]  )
    {
        statuses[status] = 0;
    }
}

int CheckForStatus( string status )
{
    if( ( (statuses[ status ] ))){
        return 1;
    }
    else {
        return 0;
    }
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

void DeathAnnounce()
{
    shout("%^BOLD%^WHITE%^RESET%^[%^RED%^DEATH%^BOLD%^WHITE%^] %^BOLD%^BLACK%^ "+ this_player()->query_cap_name()+" met an unfortunate end!\n");              
}

void SetCharGenOK(int num)
{
    playerGenDone=num;
}

int IsCharGenOK()
{
    return playerGenDone;
}

void setNewbieJob(int num)
{
	newbieJob=num;
}
int getNewbieJob()
{
	return newbieJob;
}
void setNewbieJobTotal(int num)
{
	newbieJobTotal=num;
}
int getNewbieJobTotal()
{
	return newbieJobTotal;
}
void setNewbieJobTime(int num)
{
	newbieJobTime=num;
}
int getNewbieJobTime()
{
	return newbieJobTime;
}
void checkNewbieJobTime()
{
	int seedtime=this_player()->getNewbieJobTime();
	int currenttime=time();

	if(this_player()->getNewbieJob())
	{
		if( (seedtime-currenttime) > 900)
		{
			this_player()->setNewbieJob(0);
			this_player()->setNewbieJobTime(0);
			write("[Newbie Job] Your time is up!");
		}
		
	}
}

