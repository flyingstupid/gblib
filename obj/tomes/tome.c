inherit OBJECT;


void getSuccessDisplay(int roll);
int getDiff();
void setDiff(int newDiff);
void setReadTime(int time);
int getReadTime();
int getSuccessValue(int successValue);
int diff;
int successValue;
int roll;
int readtime;

void create()
{
    set_id(({"tome", "Tome"}));
    set_short("dusty looking tome.");
    set_long("A large hardcovered tome covered in dust.");
    setReadTime(10);
    setDiff(0);
}

int getDiff()
{
   return diff;	
}

void setDiff(int newDiff)
{
    	diff=newDiff;
}

void getsuccessdisplay(int roll)
{
    write("You learn the following facts:\n");	
    return;
}

void setReadTime(int time)
{
     readtime=time;	
}

int getReadTime()
{
	return readtime;	
}
