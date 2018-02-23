inherit OBJECT;

/*function prototypes*/

int GetFill();
void SetFill(int amount);
string GetType();
void set_type(string type);

int fill;
string vesselType;


int GetFill()
{
	return fill;
}

void SetFill(int amount)
{
	fill=amount;
}

void set_type(string type){
    vesselType = type;
}

string GetType(){
    return vesselType;
}
