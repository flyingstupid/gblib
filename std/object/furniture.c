inherit OBJECT;

int CanVerb(string verb);
void SetPositions(int pos);
int GetPositions();
int GetMaxCapacity();
void SetMaxCapacity( int cap );
int GetCurrentCapacity();
void SetCurrentCapacity( int cap );
int IsFull();


int CanSit();
int CanLay();
int CanKneel();
int CanRest();
void SetCanSit();
void SetCanLay();
void SetCanKneel();
void SetCanRest();

string showAct;
string postShow;
int positions;
int currentCapacity;
int maxCapacity;

void create()
{
    set_id(({"furniture"}));
    set_short("some furniture.");
    set_long("Some furniture.");
    set("prevent_get", 1);
}

void SetPositions( int pos)
{
	positions=pos;	
}

int GetPositions()
{
	return positions;
}

void SetShowAct( string act, int pos)
{
	postShow=act;
}

string GetShowAct()
{
	return postShow;
}

int GetCurrentCapacity()
{
	return currentCapacity;
}

void SetCurrentCapacity( int cap )
{
	currentCapacity=cap;
}

int GetMaxCapacity()
{
	return maxCapacity;	
}

void SetMaxCapacity( int cap )
{
	maxCapacity=cap;
}	

int CanSit()
{
	return 0;	
}

int CanLay()
{
	return 0;
}

int CanKneel()
{
	return 0;
}

int CanRest()
{
	return 0;
}

int IsFull()
{
	return GetCurrentCapacity() >= GetMaxCapacity();	
}
