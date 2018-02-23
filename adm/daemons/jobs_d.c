/**
 * add you file header here.
 */

#define LOCATION  0
#define DIF       1
#define MAXBID    2
#define ENDTIME   3
#define BID       4
#define BIDDER    5
#define RECOVERY  6
#define CLEANOUT  7
#define DANGEROUS 8
#define GHOSTS    9
#define JOBNPC    10
#define MAXSIZE   11

#define LOC_GHOSTROOM 0
#define LOC_NAME 1
#define LOC_MOB 2
#define LOC_MAX 3

#define JOBSHOUTHEAD "%^RED%^Status%^RESET%^"

/** function prototypes */

/* This function displays all open jobs that players can bid on. */
int JobDisplay();

/* This adds jobs into the Jobs array */
int AddJob( string location, int dif, int maxTime, int maxBid, int recovery, int cleanOut, int dangerous);

/** This will get a location for the players. Its called in MakeJob() */
string GetRandomLocation();

/** Sets the players bid */
int BidJob(string jobID, int newBid);

/** writes to the player all the info on a job */
int InfoJob(string ID);

/** This generates the variables for AddJob() */
void MakeJob(int dif);

/** Saves the Daemon */
void Save();

/** is called every 2 ticks to remove jobs and if they have bids make the ghosts and place them in the ghost room */
void CleanupExpiredJobs();

/** This actually clones the ghosts and sets them up to be ready for action! */
array MakeGhosts(int dif, string loc);

/** removes a Job via the Key */
int RemoveJob( string Key );

/** This sets the job inside the won job array so we can handle it. */
void SetJob( string key, array job );

/** Returns a unique string for the ID of this Job */
string GetJobUID();

/** Clears a job from the won list */
void ClearWonJob( string jobID );

/** Adds a location to the location list */
int AddLocation( string areaID, string ghostRoom, string locationName, string locationMob );

/** DEBUG FUNTIONS */
int getTypeJobs();
int get_started(); // Sees if the engine started.
void JobShout( string message ); //Echos status updates on the jobs_d channel
mapping getjobs(); //returns the array of jobs waiting to be bid on
mapping getWonJobs(); //This returns the array of jobs that players or franchises have won bids on
/** END DEBUG FUNCTION */


//---------------------------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------------------------
int jobnum;
int ghostID;

/** list of inactive jobs */
mapping jobs;

/** List of assigned jobs */
mapping wonJobs;

/** list of valid job locations */
mapping locations;


/*These keep track of how many of what type of jobs we have in our jobs list*/
int newbieJobsMax;
int newbieJobCount;
int easyJobsMax;
int easyJobCount;
int modJobsMax;
int modJobCount;
int hardJobsMax;
int hardJobCount;
int extJobsMax;
int extJobCount;

//This keeps track of how long it takes for jobs to update.
int easyTickInterval;
int modTickInterval;
int hardTickInterval;
int extTickInterval;

/** nosave vars */
nosave int tick;
nosave int jobsMax;
nosave int started;




// Called by the driver when this object is created
void create()
{
    JobShout("Job Engine Started.");
    restore_object( "/data/daemons/jobs_d.o" );

	if( undefinedp( jobs) )              jobs = allocate_mapping( 0 );
	if( undefinedp( easyJobsMax ) )      easyJobsMax = 1;
	if( undefinedp( modJobsMax ) )       modJobsMax = 0;
	if( undefinedp( hardJobsMax ) )      hardJobsMax = 0;
	if( undefinedp( extJobsMax ) )       extJobsMax = 0;
    if( undefinedp( easyTickInterval ) ) easyTickInterval = 5;
    if( undefinedp( modTickInterval ) )  modTickInterval = 100;
    if( undefinedp( hardTickInterval ) ) hardTickInterval = 150;
    if( undefinedp( extTickInterval ) )  extTickInterval = 200;
    if( undefinedp( wonJobs ) )          wonJobs = allocate_mapping( 0 );
    if( undefinedp( locations ) )
    {
        locations = allocate_mapping( 0 );

        AddLocation( "Library", "/areas/library/libraryGhost.c", "The Library", "/areas/library/mobile/librarian.c");
    }

	tick=0;
    ghostID=0;
    set_heart_beat(1);
    jobsMax = newbieJobsMax + easyJobsMax + modJobsMax + hardJobsMax + extJobsMax;

}

int AddLocation( string areaID, string ghostRoom, string locationName, string locationMob )
{
    array locationKeys;
    array newLocation = allocate( LOC_MAX );
    string curKey;

    locationKeys = keys( locations );

    if( !areaID || areaID == "" )
    {
        return 0;
    }

    foreach( curKey in locationKeys )
    {
        if( locations[curKey][LOC_GHOSTROOM] == ghostRoom ||
            locations[curKey][LOC_NAME] == locationName ||
            locations[curKey][LOC_MOB] == locationMob )
        {
            return 0;
        }
    }

    newLocation[LOC_GHOSTROOM] = ghostRoom;
    newLocation[LOC_NAME] = locationName;
    newLocation[LOC_MOB] = locationMob;

    locations += ([ areaID:newLocation ]);

    return 1;
}

string HasJobForMob( object player, object npc )
{
    array wonJobKeys;
    array job;

    if( !player || !npc )
    {
        return 0;
    }

    wonJobKeys = keys( wonJobs );

    foreach( string Key in wonJobKeys )
    {
        job = wonJobs[ Key ];

        if( job[BIDDER] == player->query_cap_name() && 
            (get_base( npc ) + ".c") == locations[ job[LOCATION] ][LOC_MOB] )
        {
            return Key;
        }
    }

    return 0;
}

int CompleteJob( string jobKey )
{
    array job;
    array ghost;
    int bid;

    if( !jobKey || jobKey == "" )
    {
        return 0;
    }

    job = wonJobs[ jobKey ];

    if( undefinedp( job ) )
    {
        return 0;
    }

    foreach( ghost in job[GHOSTS] )
    {
        if( !undefinedp( ghost[0] ) )
        {
            return 0;
        }
    }

    bid = job[BID];

    if( this_user() )
    {
        this_user()->set_cash( this_user()->get_cash() + bid );
    }

    map_delete( wonJobs, jobKey );

    return bid;
}

int GetGhostUID()
{
    return ++ghostID;
}

void Save()
{
    //save_object( "/data/daemons/jobs_d.o" );
}

void heart_beat()
{
    tick++;

    /////////////////////
    // Every tick
    CleanupExpiredJobs();
    Save();
    /////////////////////

    if( (tick % easyTickInterval) == 0 )
    {
	    MakeJob(0);
        MakeJob(1);
    }
    
    if( (tick % modTickInterval) == 0 )
    {
        MakeJob(2);
    }
    
    if( (tick % hardTickInterval) == 0 )
    {
		MakeJob(3);
    }
    
    if( (tick % extTickInterval) == 0 )
    {
		MakeJob(4);
    }
}

array MakeGhosts(int dif, string loc)
{
    object *ghosts; 
    object newGhost;
    int pool;
    int i;
	int powermod;
	int ghostpow; 
    string file;
    int ghostID;


    // Temp way to spawn the ghost from file
    file = "/obj/npcs/ghosts/slimer.c";
    
    if( dif > 15 || dif < 0 )
    {
        JobShout( "Bad Value for DIF " + dif );
        return 0;
    }
    
	powermod = dif / 3;
    pool = dif;
    i = 0;
	
    ghosts = allocate( 0 );
	
    while( pool > 0 )
    {
	    
        ghostpow = random(pool) + powermod + 1;
		pool = pool-ghostpow - powermod;
        
        // Spawn the Ghostt
        newGhost = clone_object(file);
        ghostID = GetGhostUID();
        
        // set the ghost ID
        newGhost->SetGhostID( ghostID );

        // We need to the kill this and make it the real location
        newGhost->move(loc);
    
        // Add the ghost to the list
        ghosts += ({ ({ newGhost, ghostID })  });


        // error catch
        if( ++i > 15 )
        {
            JobShout( "Ghost spawner is trying to spawn more then 15 ghosts!" );
            return ghosts;
        }
    }

    return ghosts;
}

int RemoveJob( string Key )
{
    int dif;

    if( undefinedp( jobs[ Key ] ) )
    {
        return 0;
    }

    dif = jobs[Key][DIF];

    if( dif <= 3 )
    {
	    newbieJobCount--;
    }
    else if( dif <= 6 && dif > 3 )
    {
        easyJobCount--;
    }
    else if( dif <= 9 && dif > 6 )
    {
        modJobCount--;
    }
    else if( dif <= 12 && dif > 10)
    {
        hardJobCount--;
    }
    else if(dif <=13)
    {
        extJobCount--;
    }

    map_delete( jobs, Key );
}

void JobShout( string message )
{
    ANNOUNCE_CHDMOD->rec_m_msg( "jobs_d", JOBSHOUTHEAD, message );
}

void CleanupExpiredJobs()
{
    array job;
    string *jobKeys;
    int index;

    jobKeys = keys( jobs );

    for( index = 0; index < sizeof( jobKeys ); index++)
    {
        job = jobs[ jobKeys[ index ] ];

        if( job[ENDTIME] <= time() )
        {
            if(job[BID] > 0)
            {
                JobShout("Job bid for job ["+ jobKeys[index] +"] went to %^BLUE%^" + capitalize( job[BIDDER] ) + "%^RESET%^ for $%^GREEN%^" + job[BID] / 100 + "%^RESET%^" );
                SetJob( jobKeys[ index ], job );
            }

            RemoveJob( jobKeys[ index ] );
        }
    }
}

void SetJob( string key, array job )
{
    job[GHOSTS]  = MakeGhosts( job[DIF], locations[ job[LOCATION] ][0] );
    wonJobs[key] = job;
}

void ClearWonJob( string jobID )
{
    if( undefinedp( wonJobs[ jobID ] ) )
    {
        map_delete( wonJobs, jobID );
    }
}


int BidJob(string jobID, int newBid)
{
    array job;	
    
    CleanupExpiredJobs();

	if( undefinedp( jobs[jobID] ) )
	{
		write("There is no job with that ID!\n");
		return 1;
	}

    if( newBid < 0 ) 
    {
        write( "That isn't very sound buisness strategy try bidding a positive value...\n" );
        return 1;
    }

    job = jobs[ jobID ];

	if( newBid > job[MAXBID] )
	{
		write("Your bid of $"+ newBid +" is more than they will pay\n");
		return 1;
	}

	if( job[BID] < ( newBid * 100 ) && job[BID] != 0 )
	{
		write("Your bid of $" + newBid + " is more than the current bid.\n");
		return 1;
	}

	if( job[BID] > newBid || job[BID] == 0 )
	{
		jobs[jobID][BIDDER] = this_user()->query_cap_name();
		jobs[jobID][BID] = 100 * newBid;
		write("Your post your bid of $" +newBid+ " on job " + jobID +"\n");
        Save();
		return 1;
	}	


	return 1;

}

int InfoJob(string ID)
{
    string jobString;
    int jobDif;
    int timeLeft;    
    string jobDifString;
    string jobTaskString = "";
    array job;
    string location;

    jobString = ("%^B_WHITE%^BLACK%^| o |Job Info                                                    | o |\n");
    jobString += ("| o |============================================================| o |\n");

    job = jobs[ID];

    if( undefinedp( job ) )
    {
        jobString += sprintf("%s| o | ERROR: JOB ID NOT FOUND: %-33.33s | o |\n", "%^B_CYAN%^", ID );
        jobString += ("%^B_CYAN%^| o |============================================================| o |\n");
        jobString += ("%^RESET%^");

        write(jobString);
        return 1;
    }

    timeLeft = job[ ENDTIME ] - time();

    jobDif=job[DIF];
    if( jobDif <= 3 )
    {
	 	jobDifString="Newbie";   
    }
    else if( jobDif >= 4 && jobDif < 7 )
    {
         jobDifString="Easy";
    }
    else if( jobDif >= 7 && jobDif < 10 )
    { 
         jobDifString="Moderate";
    }
    else if( jobDif >= 10 && jobDif < 13 )
    {
         jobDifString="Hard";
    }
    else if( jobDif > 13 )
    {
         jobDifString="Extreme";
    }

    if( job[ CLEANOUT ] == 1 )
    {
         jobTaskString +="Clean Out    ";
    }

    if( job[ RECOVERY ] == 1 )
    {
         jobTaskString +="Recovery     ";
    }

    if( job[ DANGEROUS ] == 1 )
    {
        jobTaskString +="Dangerous    ";
    }

    if( jobTaskString == "" )
    {
         jobTaskString ="None";
    }

    location = locations[ job[LOCATION] ][LOC_NAME];

    jobString += sprintf("%s| o |Job Location: %-22.22sBidding Time:%-11.11s| o |\n","%^B_CYAN%^",location,sprintf( "%2.2d:%2.2d:%2.2d", timeLeft/3600, (timeLeft%3600)/60, timeLeft%60 ));
    jobString += sprintf("%s| o |Job Current Bid: %-18s Bidder: %-16.16s| o |\n","%^B_CYAN%^",sprintf( "$%d.%2.2d", job[BID]/100, job[BID]%100 ),job[BIDDER]);
    jobString += sprintf("%s| o |Job Difficulty: %-44.44s| o |\n","%^B_WHITE%^BLACK%^",jobDifString);
    jobString += sprintf("%s| o |Job Tasks: %-49.49s| o |\n","%^B_WHITE%^BLACK%^",jobTaskString);
    jobString += ("%^B_CYAN%^| o |                                                            | o |\n");
    jobString += ("%^B_CYAN%^| o |============================================================| o |\n");
    jobString += ("%^RESET%^");

    write(jobString);

    return 1;
}



//array MakeGhosts(int dif, string loc)

int AddJob(string location, int dif, int maxTime, int maxBid, int recovery, int cleanOut, int dangerous)
{
    string UID;

    CleanupExpiredJobs();

    if(sizeof( jobs ) < jobsMax)
    {
        UID = GetJobUID();
        jobs += ([ UID:allocate( MAXSIZE ) ]);

        jobs[UID][LOCATION]  = location;
        jobs[UID][DIF]       = dif;
        jobs[UID][MAXBID]    = maxBid;
        jobs[UID][ENDTIME]   = time() + ( maxTime * 60 );
        jobs[UID][BID]       = 0;
        jobs[UID][BIDDER]    = "none";
        jobs[UID][RECOVERY]  = recovery;
        jobs[UID][CLEANOUT]  = cleanOut;
        jobs[UID][DANGEROUS] = dangerous;

        Save();

        // if we add the job return 1 so we know
        JobShout("New job with difficulty of "+ dif +" posted");

        return 1;
    }   

    // if we don't add the job let the caller know
    return 0;
}


int JobDisplay()
{
    string jobString;
    
    int timeLeft;
    array job;
    string *jobKeys;
    
    CleanupExpiredJobs();

    jobString = ("%^B_WHITE%^BLACK%^| o |Job Listings                                                | o |\n");
    jobString += ("| o |============================================================| o |\n");


    jobKeys = keys( jobs );

    
    for( int i = 0; i < sizeof( jobKeys ); i++ )
    {
        job = jobs[ jobKeys[ i ] ];
   
        // Get the time left
        timeLeft = job[ENDTIME] - time();
        
        if( ( ( i + 1 ) % 2 ) == 1 )
        {
            jobString += "%^B_CYAN%^";
        }
        else
        {
            jobString += "%^B_WHITE%^BLACK%^";
        }

        jobString += sprintf( "| o |[%|6s] %-41.41s %s| o |\n", jobKeys[i], (string)( locations[ job[LOCATION] ][LOC_NAME] ), sprintf( "Diff(%|3d)", job[DIF] ) );
        jobString += sprintf( "| o |      %-44.44s %9.9s| o |\n", sprintf( "Bid( $%d.%2.2d ) Bidder( %s )", job[BID]/100, job[BID]%100, job[BIDDER] ), sprintf( "%2.2d:%2.2d:%2.2d", timeLeft/3600, (timeLeft%3600)/60, timeLeft%60 ) );
        
       
        if(i+1 >= sizeof(jobs))
	    {
		
            if( ((i+1) % 2) == 1 )
            {
                jobString += "%^B_WHITE%^BLACK%^| o |                                                            | o |\n";
                jobString += "| o |------------------------------------------------------------| o |\n";
            }
            else
            {
                jobString += "%^B_CYAN%^| o |                                                            | o |\n";
                jobString += "| o |------------------------------------------------------------| o |\n";
        	}

        }
    }
	
    write( jobString + "%^RESET%^" );
    return 1;
}

/**
 * Displays the jobs that are won for the players CORP
 */
int DisplayWonJobs()
{
	string *wonJobKeys;	
	string jobString;
    string curKey;

	wonJobKeys = keys(wonJobs);
	
	jobString =  "============================================================\n";
	jobString += "UID |Name              |Payout                              \n";
	jobString += "============================================================\n";

	for(int i = 0; i <sizeof(wonJobKeys); i++)
	{
        curKey = wonJobKeys[i];

		jobString += sprintf("[%5s] %-15.15s --- $%-s \n",curKey,wonJobs[curKey][BIDDER], GetMoneyString( wonJobs[curKey][BID] ) );
	}

	jobString += "============================================================\n";
	write(jobString);
	
	
	
	return 1;	
}

int IsLocationInUse( string testKey )
{
    array job;
    array Keys;
    string Key;

    Keys = keys( jobs );

    foreach( Key in Keys )
    {
        job = jobs[ Key ];

        if( job[LOCATION] == testKey )
        {
            return 1;
        }
    }
    
    Keys = keys( wonJobs );

    foreach( Key in Keys )
    {
        job = wonJobs[ Key ];

        if( job[LOCATION] == testKey )
        {
            return 1;
        }
    }

    return 0;
}


/** Gets a random location */
string GetRandomLocation() 
{ 
     array locKeys;
     int randomNumber;
     int keyIndex;

     locKeys = keys( locations );

     randomNumber = random( sizeof( locKeys ) ); 
     keyIndex = randomNumber;

     while( IsLocationInUse( locKeys[ keyIndex ] ) )
     {
        keyIndex = ( keyIndex + 1 ) % sizeof( locKeys );

        if( keyIndex == randomNumber )
        {
            return 0;
        }
     }

     return locKeys[ keyIndex ];
}



/** Makes the job */
void MakeJob(int dif)
{

	int recovery=0;
	int cleanOut=1;
	int dangerous=0;
	int finaldif;
    string randomLocation;

    // Make the final dif
	finaldif = dif * 3 + random( 3 ) + 1;
    finaldif = 1;

	if(dif==0)
	{
		newbieJobCount++;	
	}
	else if(dif==1)
	{
		easyJobCount++;	
	}
	else if(dif==2)
	{
		modJobCount++;
	}
	else if(dif==3)
	{
		hardJobCount++;
	}
	else
	{
		extJobCount++;
	}

    randomLocation = GetRandomLocation();

    if( randomLocation )
    {
        AddJob(randomLocation, finaldif, 1/*finaldif*5*/, finaldif*10000, recovery, cleanOut, dangerous);
    }
}


////////////////////////////////////////////////////////////////////
// Debug function to return the full array.
mapping getJobs()
{
    return jobs;
}

mapping getWonJobs()
{
	return wonJobs;	
}

int getTypeJobs()
{
	write("newbieJobsMax:"+newbieJobsMax+"\n");
	write("newbieJobCount:"+newbieJobCount+"\n");
    write("easyJobsMax:"+easyJobsMax+"\n");
    write("easyJobCount:"+easyJobCount+"\n");
    write("modJobsMax:"+modJobsMax+"\n");
    write("modJobCount:"+modJobCount+"\n");
    write("hardJobMax:"+hardJobsMax+"\n");
    write("hardJobCount:"+hardJobCount+"\n");
    write("extJobsMax:"+extJobsMax+"\n");
    write("extJobCount:"+extJobCount+"\n");
    write("Tick:"+tick+"\n");
    return 1;
}

void clearJobs()
{
    jobs = ([]);
    newbieJobCount=0;
    easyJobCount = 0;
    modJobCount  = 0;
    hardJobCount = 0;
    extJobCount  = 0;
    tick=0;
}
//End Debug
//////////////////////////////////////////////////////////////////////



//This will edit the daemon so the Admins and Dev's can change stuff on the fly.
int jobEdit(string arg, int value, string svalue)
{
	//was hoping there was an easier way....will look into it..
	write("You set " + arg + " to " + value+ "\n");
	return 1;
}

/**
 * returns a UID for the a job
 *
 * @return string - new UID
 */
string GetJobUID()
{
    string UID;
    string * letters = ({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" });

    UID = sprintf( "%s%s%4.4d", letters[random(sizeof(letters))], letters[random(sizeof(letters))], random( 10000 ) );

    while( !undefinedp( jobs[UID] ) )
    {
        UID = sprintf( "%s%s%4.4d", letters[random(sizeof(letters))], letters[random(sizeof(letters))], random( 10000 ) );
    }

    return UID;
}
