//bid.c

//Critical
//
//Command that bids on jobs from the jobs_daemon


inherit COMMAND;
int main(string arg1, string arg2)
{
    if(!arg1 || !arg2)
    {
          write("Syntax: bid <job number> <amount>\n");
          return 1;
    {
    
    
    write( "\n");
    JOBS_D->bidJob(string arg1, string arg2);
    write( "\n");
}



string help()
{
    return(HIW + " SYNTAX:" + NOR + " jobs\n\n" +
      "This command will will display all the current jobs avaliable\n"+
      "for ghostbusters to bid on. See help bid for more information\n");
}
