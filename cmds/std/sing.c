inherit COMMAND;
int main(string arg)
{
    if(!arg) {
	write("You sing to your self.\n");
	say( this_user()->query_cap_name() + " sings to themself.\n" );
	return 1;
    }
    else
    {
	write( "%^BOLD%^YELLOW%^You sing:%^RESET%^ " + arg + "\n" + NOR );
	say( "%^BOLD%^YELLOW%^" + this_user()->query_cap_name() + " sings:%^RESET%^ " +  arg + "\n" + NOR );
	return 1;
    }
}