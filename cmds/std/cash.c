//cash.c
// Written by Criticalfault + Emraef

void FunnyPrint();

int main( string arg )
{
    



    if (arg=="funny")
    {
        FunnyPrint();
    }
    else
    {
        printf( "%sCash: %s$%s%s\n", "%^BOLD%^","%^NORMAL%^GREEN%^",this_user()->get_cash_string(),"%^RESET%^" );
    }
    
    return 1;
}

void FunnyPrint()
{
    string dollar, cents;

    dollar = sprintf( "%d", this_user()->get_cash()/100 );
    cents = sprintf( "%d", this_user()->get_cash()%100 );

    if( to_int( dollar ) > 0 )
    {
        printf(" _________________________________________________\n" );
        printf("|                                                |\n" );
        printf("|  %-10s                        %10s  |\n", dollar, dollar );
        printf("|                                                |\n" );
        printf("|                   ||||||                       |\n" );
        printf("|                   (.)(.)                       |\n" );
        printf("|                     /                          |\n" );
        printf("|                    (_                          |\n" );
        printf("|                   _____                        |\n" );
        printf("|                     ,                          |\n" );
        printf("|                                                |\n" );
        printf("|  %-10s                        %10s  |\n", dollar, dollar );
        printf("|________________________________________________|\n" );
    }
    
    if( to_int( cents ) > 0 )
    {
        printf("    _____________\n" );
        printf("   /             \\\n" );
        printf("  /      %|2s       \\\n", cents );
        printf(" /                 \\\n" );
        printf("|                   |\n" );
        printf("|      ||||||       |\n" );
        printf("|      (.)(.)       |\n" );
        printf("|        /          |\n" );
        printf("|       (_          |\n" );
        printf("|      _____        |\n" );
        printf("|        '          |\n" );
        printf(" \\                 /\n" );
        printf("  \\      %|2s       /\n", cents );
        printf("   \\_____________/\n" );
    }

}
