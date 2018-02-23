inherit COMMAND;

int main(string arg)
{
    int times;
    int fd100;
    int sd100;
    int skill;
    int success;
    sscanf(arg,"%d %d",skill,times);   


    for(int i=0; i<times;i++)
    {
        fd100=random(100)+1;
        sd100=random(100)+1;

        if( random(100)+1 <= skill )
        {
            continue;
        }
        //write("Rolls:"+fd100+ " " +sd100+" "+"Skill of:"+skill);
        if(fd100 > skill && sd100 > skill)
        {
         //    write("Success!\n");
             success++;
             skill++;
         //    write("   Times took:"+i+"\n");
        }
        else
        {
          //   write("Failure\n");
        }
    }
    
    write("Successes:" +skill+"\n");


     return 1;
}
