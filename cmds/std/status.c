inherit COMMAND;

int main(string arg)
{
    mapping statuses;
    object player;
    string output;

    player = this_player();

    output =  sprintf("%sHealth: %s%d%s\n","%^BOLD%^","%^NORMAL%^RED%^",player->get_health(),"%^RESET%^" );
    output += sprintf("%sStatus:\n", "%^BOLD%^" );


    statuses = player->get_statuses();
    foreach( string status in keys( statuses ) )
    {
        output += sprintf( " %s%s %s[%s%s%s]%s\n", "%^BOLD%^GREEN%^", statuses[status][0], "%^WHITE%^", "%^RED%^", status, "%^WHITE%^", "%^RESET%^" );
    }
    
    write( output + "%^RESET%^" );
    return 1;
}

