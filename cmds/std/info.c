//tiem.c

//Emraef @ gbMUD
//02-FEB-11
//Standard command

inherit COMMAND;

int main()
{
    string output;

    output = "gbMUD was founded by Emraef and Crtical to create a fun mud, based loosely on the Ghost Busters world.\n";
     write(HIW + output  + NOR + "\n");
     return 1;
}

string help()
{
     return(HIW + " SYNTAX: " + NOR + "info\n\n" + 
     "This command give infomation about the MUD\n");     
}
