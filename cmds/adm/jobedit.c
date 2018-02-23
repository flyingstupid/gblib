inherit COMMAND;
int main ( string arg )
{
	string cmd;     //command needed for us to be able to know what you want to edit
	string svalue; //string value if it needs a string
	//string fcmd;  //final command arg
	int value;   //this is a value used for the edit. So if you want to set easyJobsMax, value is what you set it too

	if(!adminp(this_user())) 
	{
    	return notify_fail("Error [jobedit]: Access denied.\n");
	}
	sscanf(arg,"%s %d", cmd, value);

	switch( cmd )
	{
		case "easymax" :
		cmd="easyJobsMax";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "modmax" :
		cmd="modJobsMax";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "hardmax":
		cmd="hardJobsMax";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "extmax":
		cmd="extJobsMax";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "easytick":
		cmd="easyTickInterval";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "modtick":
		cmd="modTickInterval";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "hardtick":
		cmd="hardTickInterval";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
	
		case "exttick":
		cmd="extTickInterval";
		JOBS_D->jobEdit(cmd, value, svalue);
		break;
		
		default:
		return notify_fail("Error [jobedit]: Must be a value in range.\n"); 
		break;
	}
	write("Failure!\n");
	return 1;
}



string help()
{
    return(HIW + " SYNTAX:" + NOR + " jobedit <arg> <value>\n\n" +
      "This command will change the Jobs Daemon variables.          \n"+
      "Arguments for this command are as follows:                   \n"+
      "easymax, modmax, hardmax, extmax, easytick, modtick, hardtick\n"+
      "exttick.                                                     \n");
}
