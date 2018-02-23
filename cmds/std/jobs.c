//jobs.c

//Critical
//
//Command that displays job from JOBS_D.c or the jobs daemon.

inherit COMMAND;

int bid( string arg );
int list( string arg );
int info( string arg ); 
int complete( string arg );
int SyntaxFail();

int main(string arg)
{
    string cmd;
    string cmdArgs;

    if( !arg || arg == "" )
    {
        return SyntaxFail();
    }

    if( sscanf(arg, "%s %s", cmd, cmdArgs ) != 2 )
    {
        cmd = arg;
        cmdArgs = "";
    }

    switch( cmd )
    {
        case "bid":
            return bid( cmdArgs );
            break;
        case "list":
            return list( cmdArgs );
            break;
        case "info":
            return info( cmdArgs );
            break;
        case "complete":
            return complete( cmdArgs);
            break;
      
     }


    return SyntaxFail();
}
   
int SyntaxFail()
{
    return notify_fail( "[SYNTAX] jobs bid <jobNumber> <bid>\n"
                        "[SYNTAX] jobs list\n"
                        "[SYNTAX] jobs complete\n");
}

int bid( string arg )
{
    string jobID;
    int jobBid;
    
    if( sscanf( arg, "%s %d", jobID, jobBid ) != 2 )
    {
        return notify_fail( "[SYNTAX] jobs bid <jobID> <bid>\n" );
    }

    JOBS_D->BidJob(upper_case(jobID),jobBid);

    return 1;
}

int list( string arg )
{
    call_out( "printJobs", 5 );
    write( "You here the soothing sounds of a dot matrix printer.\n" );
    return 1;
}

int info( string arg )
{
    JOBS_D->InfoJob( upper_case(arg) );
    return 1;
}

int complete( string arg )
{
    object ob;
    string jobID;
    int wonJobCash;

    foreach( ob in all_inventory( environment( this_user() ) ) )
    {
        if( !is_a( MOBILE, ob ) || is_a( PLAYER, ob ) )
        {
            continue;
        }

        jobID = JOBS_D->HasJobForMob( this_user(), ob );

        if( !jobID )
        {
            continue;
        }

        wonJobCash = JOBS_D->CompleteJob( jobID );

        if( wonJobCash )
        {
            write( "Job Completed!  You have earned yourself $" + GetMoneyString( wonJobCash ) + ".\n" );
            return 1;
        }
        else
        {
            write( "You have not completed Job '" + jobID + "' yet.\n" );
            return 1;
        }
    }
    
    write( "You cannot complete any jobs here.\n" );
    return 1;
}



void printJobs()
{
    write( "\n" );
    JOBS_D->JobDisplay();
    write( "\n" );
}

string help()
{
    return(HIW + " SYNTAX:" + NOR + " jobs\n\n" +
      "This command will will display all the current jobs avaliable\n"+
      "for ghostbusters to bid on.\n");
}
