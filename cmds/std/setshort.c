//setshort by critical

inherit COMMAND;

int main(string arg)
{

     if(!arg)
     {
          write("syntax: setshort <Short description>\n");
          return 1;
     }
     this_player()->set_short(arg);
     write("You change your short to:" +arg +"\n"); 
     return 1;

}
