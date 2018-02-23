//Skills.c
//Written by Criticalfault



int main()
{
string *keysArray = keys(this_user()->get_skills()); 
string name = this_user()->query_name();
   
    write("|======[Skills - "+ sprintf("%10s",capitalize(name)) + "]=======|\n");
    
    for(int i=0; sizeof(keysArray)>i; i++)
    {    
    	printf( "| %-19s:%-12d |\n", keysArray[i],this_user()->get_skill(keysArray[i])  );
    }


    write("|==================================|\n");



    return 1;
}
