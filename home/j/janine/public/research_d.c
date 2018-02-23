//
//  research_d.c
//  GB mud
//

#define RPLAYER         0
#define RTYPE           1
#define RSTARTTIME      2
#define RSAMPLE         3
#define RPOINTS         4
#define RPREPTIME       5


#define RSSHOUTHEAD "RESEARCH"

/*function prototypes*/
int AddProject(string type, string sample);
string GetProjectID();


string GetCommand( string arg );
object GetItem( string arg );


//displays info on samples in preparation
void DisplayPreps();

//function to return jobs and amount of time left until prep is complete
//function to remove old jobs
//function to add resarch points ot player profile
//function to check if the prep job is complete


/*variables*/
mapping projects;


/* called to create the object */
void create(){
    string type;
    string sample;
    
    
   // restore_object( "/data/daemons/research_d.o" );
    
    if ( undefinedp( projects) )        projects = allocate_mapping ( 0 );
    AddProject(type, sample);    
}


/*used for debugging purposes*/
void ResearchShout( string message )
{
    ANNOUNCE_CHDMOD->rec_m_msg( "research_d", RSSHOUTHEAD, message );
}


/* called when player prepares an item*/
int AddProject(string type, string sample){
    string PID;
    int points;
    int prepTime;

    
    PID = GetProjectID();
    
    
    projects [PID][RPLAYER]        = this_player();
    projects [PID][RSTARTTIME]     = time();
    projects [PID][RTYPE]          = type;
    projects [PID][RSAMPLE]        = sample;
    projects [PID][RPOINTS]        = points;
    projects [PID][RPREPTIME]      = prepTime;
    
    ResearchShout(this_player()->query_cap_name() + " has begun preparing a sample\n");
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



/*Displays Information on current projects in preparation*/

void DisplayPreps(){
    string prepString;
    int playerOnlineTime = 100;
    int playerOnlineTime2 = 200;
    
    prepString = 
    "==============================[LABORATORY]==================================\n";
    prepString += "The following projects are being prepared in the Laboratory:\n";
    
    for( int i = 0; i < this_player()->GetNumProjects(); i++){
 
        prepString += "a vial of slime requres approximatly XXX more minutes of preparation\n";
    }
    prepString += "============================================================================\n";
    
    
}


int query_wait_type( string arg )
{
	if( !arg || arg == "" )
	{
        return 5;
	}
    
    return 3;
}



int query_wait_time( string arg )
{
	
	string cmd;
	object researchItem;
	
	
	if( !arg || arg == "" )
	{
        return 0;
	}
	
    
	
	cmd = GetCommand( arg );
    researchItem = GetItem( arg );
    
    
    if(cmd=="examine")
    {
	    return researchItem->GetResearchTime()*1000;
    }
    else if(cmd=="prepare")
    {
	    return researchItem->GetResearchTime()*2000;
    }
    else
    {
	 	return 1000;   
    }
	
	
    return 0;
}

string GetCommand( string arg )
{
    string cmd, itemName;
    
    if( sscanf(arg, "%s %s", cmd, itemName) != 2 )
    {
        return arg;
    }
    
    return cmd;
}

object GetItem( string arg )
{
    string cmd, itemName;
    object item;
    
    if( sscanf(arg, "%s %s", cmd, itemName) != 2 )
    {
        return 0;
    }
    
    item = present( itemName, this_user() );
    
    if( !item ){
        write("item isn't here");
        return 0;
    }
    
    
    else if(!is_a( SAMPLE, item ) )
    {
        write("not a sample");
        return 0;
    }
    
    write("found sample");
    return item;
}



