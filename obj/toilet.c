inherit FURNITURE;

/* Variables  */
int fill=0;

/* Function Prototypes*/
void SetFill(int _fill);
int GetFill();
string GetDisplay();

void create()
{
    set_id(({"golden", "toilet"}));
    set_short("A golden toilet");
    set_long("A comfortable looking gold toilet.\n"+GetDisplay()+"\n");
    set("prevent_get", 1);
    SetCurrentCapacity(0);
    SetMaxCapacity(1);
    SetFill(0);
    CanSit();
    
}
int CanSit()
{
     return 1;
}



/* Functions */
void SetFill( int _fill)
{
	fill=_fill;
}

int GetFill()
{
	return fill;
}

string GetDisplay()
{
	if(GetFill()==1)
	{
		return "The toilet seems to have been used...";
	}
	else
	{
		return "The toilet is clean and ready to be used!";	
	}
	
		
	
}