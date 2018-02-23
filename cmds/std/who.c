/* who.c

 Tacitus @ LPUniversity
 06-FEB-07
 Standard command
 
*/

inherit COMMAND;

string renderTag(string rank);
string array sortRankIndex(string array ranks);
string make_wholist();
string whotitle(object user);
string RenderName( object user );
string format_idle_time(int time);


int main(string arg)
{
    string mudname, who_list;

    if (arg && sscanf(arg, "@%s", mudname) == 1)
    {
        "/adm/daemons/chmodules/i3.c"->send_packet(
            ({ "who-req", 5, mud_name(), this_player()->query_name(), mudname, 0 })
        );
        return 1;
    }

    who_list = make_wholist();
    printf("%s\n", who_list);

    return 1;
}

string make_wholist()
{
    string output;
    int numberOfStaff;
    int numberOfPlayers;
    
    output = "%^RED%^           ______          %^WHITE%^ _\n"
             "%^RED%^           | ___ \\         %^WHITE%^| |\n"
             "%^RED%^           | |_/ /_   _ ___%^WHITE%^| |_ %^BLUE%^___ _ __ ___\n"
             "%^RED%^           | ___ \\ | | / __%^WHITE%^| __/%^BLUE%^ _ \\ '__/ __|\n"
             "%^RED%^           | |_/ / |_| \\__ %^WHITE%^\\ |%^BLUE%^|  __/ |  \\__ \\\n"
             "%^RED%^           \\____/ \\__,_|___/%^WHITE%^\\_\\%^BLUE%^\\___|_|  |___/\n%^RESET%^";

    numberOfStaff = sizeof( users() ) - sizeof( RANK_D->getInteractives("user") );
    numberOfPlayers = sizeof( RANK_D->getInteractives("user") );
    
    if( numberOfStaff > 1 )
    {
        output += sprintf( "%s==============[%sThere are %|3d Staff Online%s]==============%s\n", "%^BOLD%^WHITE%^","%^NORMAL%^RED%^", numberOfStaff, "%^BOLD%^WHITE%^", "%^RESET%^" );
    }
    else if( numberOfStaff > 0 )
    {
        output += sprintf( "%s==============[%sThere is  1  Staff Online%s]===============%s\n", "%^BOLD%^WHITE%^","%^NORMAL%^RED%^", "%^BOLD%^WHITE%^", "%^RESET%^" );
    }

    foreach(string rank in sortRankIndex(RANK_D->getRanks()))
    {
        if( rank == "user" && numberOfPlayers > 1 )
        {
            output += sprintf( "%s=============[%sThere are %|3d Busters Online%s]=============%s\n", "%^BOLD%^WHITE%^","%^NORMAL%^RED%^", sizeof( RANK_D->getInteractives(rank) ), "%^BOLD%^WHITE%^", "%^RESET%^" );
        }
        else if( rank == "user" && numberOfPlayers > 0 )
        {
            output += sprintf( "%s==============[%sThere is  1  Buster Online%s]==============%s\n", "%^BOLD%^WHITE%^","%^NORMAL%^RED%^", "%^BOLD%^WHITE%^", "%^RESET%^" );
        }

        foreach(object user in RANK_D->getInteractives(rank))
        {
            output += sprintf(" %-s   %-36s %6s\n", renderTag(rank),
                                                     RenderName( user ),
                                                     format_idle_time( query_idle( user ) ) );
        }
    }
    
    return output;
}

string renderTag(string rank)
{
    string tag;

    if( rank == "user" )
    {
        return "%^BOLD%^WHITE%^[%^RESET%^ %^GREEN%^GBA%^RESET%^   %^BOLD%^WHITE%^]%^RESET%^";
    }

    tag = sprintf( "%s[%s %s%-5.5s %s]%s", "%^BOLD%^WHITE%^", "%^RESET%^",
                                             RANK_D->queryRankProperty( rank, "colour" ), 
                                             capitalize(RANK_D->queryRankProperty(rank, "short")),
                                             "%^BOLD%^WHITE%^", "%^RESET%^" );
    return tag;
}

string array sortRankIndex(string array ranks)
{
    string array returnValue = ({});
    int i = sizeof(ranks);
    
    while(i--) returnValue += ({ ranks[i] });
        
    return returnValue;    
}

string whotitle(object user)
{
	string title;
	title=user->query_title();
	
	if(title==0)
	{
		return "";
	}
	else
	{
		return title;	
	}
	
	
}

string RenderName( object user )
{
    string title;
    string pretitle;
    string name;

    if( !user )
    {
        return "no Name";
    }

    title = user->query_title();
    pretitle = user->query_pretitle();
    name = user->query_cap_name();

    if( !title )
    {
        title = "";
    }

    if( !pretitle )
    {
        pretitle = "";
    }

    if( !name )
    {
        name = "no Name";
    }

    if( user->query_env( "away" ) )
    {
        name = "(" + name + ")";
    }
    else if( in_edit( user ) )
    {
        name = "{" + name + "}";
    }
    else if( in_input( user ) )
    {
        name = "[" + name + "]";
    }

    if( pretitle != "" )
    {
        pretitle += " ";
    }

    return sprintf( "%s%s %s", pretitle, name, title );

}

string format_idle_time(int time)
{
    int seconds;
    int minutes;
    int hours;
    int days;

    days = time / 60 / 60 / 24;

    if( days > 1 )
    {
        return sprintf( "%dd", days );
    }

    hours = (time / 60 / 60) % 24;

    if( hours > 1 )
    {
        return sprintf( "%dh", hours );
    }

    seconds = time % 60;
    minutes = (time / 60) % 60;

    return sprintf( "%dm", minutes );
}


string help()
{
    return(HIW + " SYNTAX: " + NOR + "who [@<mud>]\n\n" +
      "This command will display all the users who are currently logged\n" +
      "into " + mud_name() + ". It also lets you know if they are currently\n" +
      "editing, in input, and/or idle. You may also find out who is on a mud\n" +
      "on the I3 network by using the 'who @<mud>' syntax\n");
}


