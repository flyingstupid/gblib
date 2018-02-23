inherit OBJECT;
string set_date();

void create()
{
     set_id(({"grave", "gravestone", "headstone", "stone", "tombstone"}));
         set_short("A gravestone");
         set_long(this_player()->query_cap_name() +"\n"
              + "Mar 14 1967 - " + set_date() +"\n"
                 );
        set("prevent_get", 1);
}
         /*Used to make ctime format as abbr Month Date Year*/
string set_date()
{ 
     string date; 
	 string *dateArray; 
	 date = ctime( time() ); 
	 dateArray = explode( date, " " ); 
	 return( dateArray[1] + " " + dateArray[2] + " " + dateArray[4]); 
}
