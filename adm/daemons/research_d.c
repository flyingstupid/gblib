//
//  /adm/daemons/research_d.c
//  GB mud
//

#define RPLAYER         0
#define RTYPE           1
#define RSTARTTIME      2
#define RSAMPLE         3
#define RPOINTS         4
#define RPREPTIME       5
#define RESEARCHSIZE    6


#define RSSHOUTHEAD "RESEARCH"

/*function prototypes*/
void ResearchShout( string message );
void AddProject(object sample, object player);
string GetProjectID();


//displays info on samples in preparation
void DisplayPreps();

//caclculates the number of points to award the player for successful research
int CalcResearchPoints(object sample);

//function to return jobs and amount of time left until prep is complete
//function to remove old jobs
void ProcessOldProjects();


//function to add resarch points ot player profile
//function to check if the prep job is complete


/** Saves the Daemon */
void Save();


/*variables*/
mapping projects;

/* nosave vars */
nosave int tick;


/* called to create the object */
void create(){
   restore_object( "/data/daemons/research_d.o" );
    
    if ( undefinedp( projects) )        projects = allocate_mapping ( 0 );
    
    tick = 0;
    set_heart_beat(1);
}


/*used for debugging purposes*/
void ResearchShout( string message )
{
    ANNOUNCE_CHDMOD->rec_m_msg( "research_d", RSSHOUTHEAD, message );
}


/* called when player prepares an item*/
void AddProject(object sample, object player){
    string PID;
    int points;
    //int newsize;
    
    
    
    points = CalcResearchPoints(sample);
    
    PID = GetProjectID();
    
    tell_object(this_player(), player->query_cap_name() + " begins to examine a "+ sample->query_short() + "\n");
    
    
    //this needs cleaned up!
    projects += ([ PID:allocate( RESEARCHSIZE ) ]);
    
    
    projects [PID][RPLAYER]        = player;
    projects [PID][RSTARTTIME]     = time();
    projects [PID][RTYPE]          = sample->query_short();
    projects [PID][RSAMPLE]        = sample;
    projects [PID][RPOINTS]        = sample->GetResearchValue();
    projects [PID][RPREPTIME]      = sample->GetPrepTime();
    
    this_player()->SetNumProjects(1);
}



/*Displays Information on current projects in preparation*/

void DisplayPreps(){
    string prepString;
    array projectKeys;
    string key;
    array project;
    int timeLeft;
    

    
    
    projectKeys = keys( projects );
    
    prepString = 
    "==============================[LABORATORY]==================================\n";
    prepString += "The following projects are being examined in the Laboratory:\n";
    
    foreach( key in projectKeys ){
        project = projects [key];
        if (project[RPLAYER] == this_player()){
            timeLeft = ((project[RPREPTIME] - (time()-project[RSTARTTIME]))/60);
            prepString +="Project: " + key +"\n";
            prepString +="type: " + project[RTYPE] + "\n";
            if (timeLeft<=0){
                prepString +="This sample has been completely examined and the results have been logged.\n\n";
            }
            else{
            prepString +="Approximate prep time remaining: " + timeLeft + " minutes.\n\n";
            }
        }
    }
    prepString += "============================================================================\n";
    
    write(prepString);
    
    ProcessOldProjects();
    Save();
}


//caclculates the number of points to award the player for successful research
int CalcResearchPoints(object sample){
    int researchValue;
    string sampleName;
    
    sampleName = sample->query_short();
    
    //write("the sample is " + sampleName + "\n");
    researchValue = (sample->GetResearchValue() * sample->get_collect_value());
    //there will be something in here to account or fumbled collection
    return researchValue;
}


/*returns a ID for the Project*/

string GetProjectID(){
    string UID;
    string * letters = ({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
        "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" });
    
    UID = sprintf( "%s%s%4.4d", letters[random(sizeof(letters))], letters[random(sizeof(letters))],
                  random( 10000 ) );
    
    while( !undefinedp( projects[UID] ) )
    {
        UID = sprintf( "%s%s%4.4d", letters[random(sizeof(letters))],
                      letters[random(sizeof(letters))], random( 10000 ) );
    }
    
    return UID;
}


void ProcessOldProjects(){
    array projectKeys;
    string key;
    array project;
    int timeLeft;
    
    
    projectKeys = keys( projects );
   // write ("Processing old projects");
    
    foreach( key in projectKeys ){
        project = projects [key];
        timeLeft = ((project[RPREPTIME] - (time()-project[RSTARTTIME]))/60);
            
            if (timeLeft <= 0){
                //write ("You have finished preparing " + project[RTYPE] + "\n");
                project[RPLAYER]->SetResearchTotal(project[RPLAYER]->GetResearchTotal()+project[RPOINTS]);
                project[RPLAYER]->SetNumProjects(-1);
                map_delete( projects, key );
            }
    }

}


void Save()
{
    save_object( "/data/daemons/research_d.o" );
}


