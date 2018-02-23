inherit COMMAND;

int main( string arg )
{
	object potty;
	
	
	if(!arg)
	{
		write("SYNTAX: use <toilet> \n");
		return 1;	
	}
	
	
	potty=present(arg, environment(this_player()));
	
	if(!potty)
	{
		write("You can't find " + arg + " here.\n");	
		return 1;
	}
	
	if(this_player()->GetBladder()==0)
	{
		write("You don't need to use the bathroom.\n");
		return 1;	
	}
	
	
	
		if(potty->GetFill()==1)
		{	
			write("Eww...someone forgot to flush!\n");
			return 1;
		}
	
	if(is_a(TOILET, potty))
	{
		write("You relieve yourself.\n");	
		say(this_player()->query_cap_name()+ " relieves themselves.\n");
		this_player()->SetBladder(0);		
		potty->SetFill(1);
		return 1;	
	}
	else
	{
		write("Your going to use THAT for THAT?\n");
		return 1;
	}
	
	
	return 1;	
}



