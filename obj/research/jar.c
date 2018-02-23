inherit SAMPLE;


int GetFill();
void SetFill(int amount);


int fill;
string name;

	
void create()
{
    set_id(({"glass", "jar", "Glass", "Jar"}));
    set_short("a glass jar");
    set_long ("a glass jar");
    SetResearchValue(0);
    SetResearchTime(0);
    SetResearchChance(0);
    SetResearchQuality(0);
    SetResearchPrepared(0);
    
}	
	
	
int GetFill()
{
	return fill;
}

void SetFill(int amount)
{
	fille=amount;
}


