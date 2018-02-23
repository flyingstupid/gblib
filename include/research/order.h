
//
// /include/research/order.h
//  GB mud
//


inherit COMMAND;

//FUNCTION PROTOTYPES
void equipment_list();
void place_order(object equipment);
string get_file(string name);
void does_accept(string response);
void finalize_order(int accept);
void inst_eq();

//GLOBAL VARIABLES
int accept;
object equipment;

int main (string arg){
    
    string fileName;
    
    if ( !arg ){
        equipment_list();
        return 0;
    }
    
    fileName = get_file(arg);
    write(fileName + "\n");
    
    load_object(fileName);
    equipment = find_object(fileName);
    
    write(fileName + "\n");
    
      
    if (equipment){
        write(equipment->query_short() + "\n");
    }
    
    
    if (!equipment)
    {
        write("object not found\n");
        return 0;
    }
    
    if  (!is_a("/obj/research/equipment.c", equipment))
    {
        write("not equipment\n");
        return 0;
    }
        
    
    write ("This equpiment costs " + equipment->get_cost() + ", you have " + this_player()->get_cash()  + ".\n");
    
    if(this_player()->get_cash()< equipment->get_cost())
    {
        write("You can't afford that item!\n");
        return 0;
    }
    
    tell_object (this_player(), "Your order has been placed, expect delivery shortly.\n");
    call_out ("place_order", 5, equipment);
    
    return 1;
}



void equipment_list()
{
    string equipString;
    
    equipString = "==============================[EQUIPMENT]==================================\n\n";
    equipString += "Fabricating Machine - Permits the fabrication of laboratory equpiment such as test tubes\n";
    equipString += "cost:  $300,000     Certification required:  Fabricate \n";
    equipString += "Installation location: Main Laboratory \n\n";
    equipString += "Slime extractor - Permits the extraction of antislime from ghost slime\n";
    equipString += "cost:  $400,000     Certification required:  Extract \n";
    equipString += "Installation location: Slime annex \n\n";
    equipString += "Purifier - Permits the purification of luquid samples into serums\n";
    equipString += "cost:  $550,000     Certification required:  Purify \n";
    equipString += "Installation location: liquid Laboratory \n\n";
    write (equipString);
    
}

void place_order(object equipment){
    
    write ("A burly delivery man clamers into the room and looks around. He \n"
           "says to " + this_player()->query_name() + " Did you order a "+ equipment->query_short() + "?\n"
           "If so, just say the word to ACCEPT it and I'll install it right away!\n");
    
    input_to("does_accept");
    
    return;
}


void does_accept(string inpt){
    if (inpt == "yes" || inpt == "Yes" || inpt == "y" || inpt == "Y" || inpt == "accept" || inpt == "Accept"){
        accept = 1;
    }
    if (inpt == "no" || inpt == "No" || inpt == "n" || inpt == "N" || inpt == "reject" || inpt == "Reject"){
        accept = 0;
    }
    
    finalize_order(accept);
}


void finalize_order(int accept){
    
    if ( !accept ){
        write ("The burly delivery man grumbles a few times, mutters some choice words\n"
               "under his breath and stomps out\n");
        return;
    }

    if (equipment->query_short() == "fabricating machine" && is_a ("/areas/research/labroom.c", environment(this_player())))
    {
        inst_eq();
        return; 
    }
    
    if (!environment(this_player())->query_exit(equipment->get_location()))
    {
        write ("The burly delivery man says hey, building codes only allow me to place\n"
               "this in a " + equipment->get_location() + " annex.  Order again after you've had one built.\n");
        return;
    }
    inst_eq();
    return;    
}


void inst_eq(){
    string locationName;
    object location;
    
    if (equipment->query_short() == "fabricating machine")
    {
        location = environment(this_player());
    }
    
    else
    {
        locationName = (environment(this_player())->query_exit(equipment->get_location()));
        load_object(locationName);
        location = find_object(locationName);
    }

    equipment->move(location);
    
    write ("The delivery man tips his cap in " +this_player()->query_short() + "'s direction and says\n"
           "All set there!, as he leaves\n");
}

string get_file(string name)
{
    mapping objMap;
    
    objMap = (["tube":"/obj/research/tube.c",
               "Tube":"/obj/research/tube.c",
               "test tube":"/obj/research/tube.c",
               "Test tube":"/obj/research/tube.c",
               "vial": "/obj/research/vial.c",
               "Vial": "/obj/research/vial.c",
               "bag": "/obj/research/bag.c",
               "sample bag": "/obj/research/bag.c",
               "Sample bag": "/obj/research/bag.c",
               "Bag": "/obj/research/bag.c",
               "Fabricator":"/obj/research/fabricator.c",
               "fabricator":"/obj/research/fabricator.c",
               "Fabricating machine":"/obj/research/fabricator.c",
               "fabricating machine":"/obj/research/fabricator.c",
               "machine":"/obj/research/fabricator.c",
               "Machine":"/obj/research/fabricator.c",
               "extractor":"/obj/research/extractor.c",
               "Extractor":"/obj/research/extractor.c",
               "purifier":"/obj/research/purifier.c",
               "Purifier":"/obj/research/purifier.c",
               ]);
    
    return objMap[name];
}



string help()
{
    return(HIW + " SYNTAX: " + NOR + "order [equipment name]\n\n"
           "This command allows the you to order lb equipment for delivery.\n"
           "Equpiment will be delivered and installed.  Once installed, equipment\n"
           "can not be moved.\n"
           "For a list of available equipment just type order.\n");
}





