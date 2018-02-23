inherit COMMAND;

int main ( string arg )
{
	object toilet;
	if(!arg)
	{
		write("SYNTAX: flush toilet \n");	
		return 1;
	}	
	toilet=present(arg, environment(this_player()));
	
	if(!toilet)
	{
		write("You can't find " + arg + ".\n");	
		return 1;
	}
	

	
	toilet->SetFill(0);
	write("You flush the toilet.\n");
	say(this_player()->query_cap_name() + " flushes " + toilet->query_short() + ".\n");
	return 1;
	
	
}