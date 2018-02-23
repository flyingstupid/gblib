inherit COMMAND;

int main (string arg)
{	
	if(strlen(arg) > 25 )
	{
		write("Your title can only be 25 characters long.\n");
		return 1;
	}
	else
	{
	this_user()->set_title(arg);	
	write("You set your title to: " + arg + "\n");
	return 1;
	}	
}