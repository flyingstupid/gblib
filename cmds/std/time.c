//tiem.c

//Emraef @ gbMUD
//02-FEB-11
//Standard command

inherit COMMAND;

int main()
{
     write(HIW + ctime()  + NOR + "\n");
     return 1;
}

string help()
{
     return(HIW + " SYNTAX: " + NOR + "time\n\n" + 
     "This command tells you the server time.\n");     
}
