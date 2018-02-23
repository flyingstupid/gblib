/* clear.c
Icoz @ LPUniversity
21-MAY-06
Standard command

*/
inherit COMMAND;
int main(string str)
{
    if( !str )
    {
        write( "Current prompt: " + this_user()->query_env( "prompt" ) + "\n" );
    }
    else if( str == "default" )
    {
        this_user()->set_env( "prompt", DEFAULT_PROMPT );
    }
    else
    {
        this_user()->set_env( "prompt", str );
    }

	return 1;
}

string help()
{
    string returnString;
	returnString = (HIW + "SYNTAX: " + NOR + "prompt [promptstring]\n\n" +
	"This command will set your prompt. %^CYAN%^prompt default%^RESET%^ will\n" + 
    "set your prompt to the default prompt The following \n" + 
    "options are avalible:\n\n" );

    if( devp( this_user() ) )
    {
        returnString += ( "%d - Current working directory\n" +
                          "%f - Current wroking file\n" +
                          "%u - number of users\n" +
                          "%l - filename of your environment\n" );
    }
    
    returnString += ( "%n - Your Name\n" +
                      "%m - The mud name\n" +
                      "%T - Time with seconds\n" +
                      "%t - Time with out seconds\n" +
                      "%D - Date with day of the week\n" +
                      "%d - Date without day of the week\n" +
                      "%W - Wait timer (hidden if 0)\n" +
                      "%w - Wait timer (shown if 0)\n" +
                      "$W - colored and formatted wait time %^BOLD%^[%^MAGENTA%^9.87%^WHITE%^]%^RESET%^\n" +
                      "$n - a new line\n" );

    return returnString;
}
