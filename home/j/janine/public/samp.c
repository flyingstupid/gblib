/* sample.c - base code fo the production of research samples*/


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
string GetVessel();
void SetVessel(string vessel);
int GetIsFull();
int setIsFull(int full);


int researchValue;
int researchTime;
int researchChance;
float researchQuality;
int researchPrepared;
int wasFumbled;
string collectionVessel;



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

string GetVessel()
{
	return collectionVessel;
}

void SetVessel(string vessel)
{
	collectionVessel = vessel;
}

