//quit.c

//Tacitus @ LPUniversity
//06-APR-05
//User command

//Last edited on October 8th, 2005 by Tacitus
inherit COMMAND;

#include <logs.h>
#include <config.h>

int main(string arg)
{
     this_user()->exit_world();
     write("Thank you for visiting " + mud_name() + "\n");
     this_user()->save_user();
     log_file(LOG_LOGIN, capitalize(this_user()->query_name()) + " logged out from " +
     query_ip_number(this_user()) + " on " + ctime(time()) + "\n");
     destruct(this_user());
     return 1;
}

string help()
{
     return(HIW + " SYNTAX:" + NOR + " quit\n\n" +
     "This command will save your characher and disconnect you from the mud.\n\n" +
     HIW + "See also: " + NOR + "save\n");
}
