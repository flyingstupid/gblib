inherit OBJECT;

int GetResearchValue();
void SetResearchValue(int value);
int GetResearchTime();
void SetResearchTime(int time);
int GetResearchChance();
void SetResearchChance(int chance);
float GetResearchQuality();
void SetResearchQuality(int quality);
int IsResearchItem();
void SetResearchPrepared(int prep);
int IsResearchPrepared();
int GetWasFumbled();
void SetWasFumbled(int val);


int researchValue;
int researchTime;
int researchChance;
float researchQuality;
int researchPrepared;
int wasFumbled;

void create()
{
    set_id(({"sample", "slime", "Slimer", "Sample"}));
    set_short("some slime");
    set_long ("a puddle of slime");
    SetResearchValue(100);
    SetResearchTime(15);
    SetResearchChance(100);
    SetResearchQuality(1);
    SetResearchPrepared(0);
    SetWasFumbled(0);
    
}


int GetResearchValue()
{
	return researchValue;
}

int GetResearchTime()
{
	return researchTime;
}

int GetResearchChance()
{
	return researchChance;
}

int GetResearchQuality()
{
	return researchQuality;
}

void SetResearchValue(int value)
{
	researchValue=value;	
}

void SetResearchTime(int time)
{
	researchTime=time;	
}


void SetResearchChance(int chance)
{
	researchChance=chance;	
}

void SetResearchQuality(int quality)
{
	researchQuality=quality;	
}

int IsResearchItem()
{
	return 1;	
}

void SetResearchPrepared(int prep)
{
	researchPrepared=prep;
}

int GetResearchPrepared()
{
	return researchPrepared;
}

int GetWasFumbled()
{
	
	return wasFumbled;
	
}

void SetWasFumbled(int val)
{
	wasFumbled=val;	
	
}
