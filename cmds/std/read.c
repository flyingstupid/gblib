inherit COMMAND;

int read(object book);

int main(string arg)
{
     object book;
     object *inv;

      if(!arg)
      {
            write("SYNTAX: read <book>\n");
            return 1;
      }

      for(int i=0; i < sizeof( inv ); i++)
      { 

         if((book)  &&  is_a ("/obj/tomes/tome.c", book) )
         {
             book=inv[i];
             write("You begin to read into your tome carefully.\n");
             call_out("read", book->getReadTime(),book);  
             //read(book);
             break;
         }
         else
         {
             write("Thats not a tome!\n");
             return 1;
         }
      }
         

}


int read(object book)
{
    int success;

   success=this_player()->DoSkillRoll("research",book->getDiff());
   if(success>0)
   {
     book->getsuccessdisplay(success);
     return 1;
   }
   else
   {
      write("You learn nothing from your studies.\n");    

      return 1;
   }
}   
