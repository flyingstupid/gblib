inherit ROOM;

void create()
{
     set_light(1);
     set_short("Tools of the trade");
     set_long(
          "As a ghostbuster you'll need to be able to catch ghosts! The of a proton pack\n"
          "and ghost trap will be required. The easiest way to find a ghost as well will\n"
          "be to use a PKE Meter. Look at the sign to explain how to use those objects  \n"
          
     );
     set_exits( ([
           "south" : "/areas/academy/academy3.c",

]) );
     set_items( ([
          "sign" : "The sign reads:\n"
               "This room will cover the commands of: SHOOT, THROW MAKEREADING\n"
               "\n%^GREEN%^SHOOT%^RESET%^:This command is your primary attack against ghosts. The\n"
               "command is used like the example below. The proton pack must be used with a frequency.\n"
               "Every ghost in the mud has a frequency. It can only be captured once you find it. To\n"
               "find a ghosts frequency you attempt to shoot it at random or get a good PKE Reading.\n"
               "Your proton packs will let you know if your frequency is too high or too low.\n" 
               "A %^BOLD%^CYAN%^Cyan%^RESET%^ light means your frequency is too high.\n"
               "A %^YELLOW%^Yellow%^RESET%^ light means your frequency is too low.\n"
               "A %^BOLD%^GREEN%^Green%^RESET%^ light means your frequency is dead on.\n"
               "Example:Shoot slimer 50\n"
               "\n%^GREEN%^THROW%^RESET%^:Once you have a ghost captured you will need to seal it in a\n"
               "a ghost trap. To do this, you simply have a ghost trap in your inventory and THROW <TRAP> <TARGET>\n"
               "Such as: throw trap slimer\n" 
               
               "\n%^GREEN%^MAKEREADING%^RESET%^: When holding a PKE meter a character can get a basic\n"
               "reading. A skill roll will determine the results so if you get a big range. Let your\n"
               "proton pack help guide you the rest of the way.\n\n"
,]) );
}