inherit COMMAND;

int main(string arg)
{
	int dif;
	sscanf(arg ,"%d", dif);
	
	if( dif <= 12 && dif > 10 )	
	{
		write("returns true\n");	
	}
	else
	{
		write("returns false\n");
	}
	
	return 1;
	
}