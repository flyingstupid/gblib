//
//  /obj/research/computer.c
//  GB mud
//

inherit OBJECT;
inherit COMMAND;

//FUNCTION PROTOTYPES
void equipment_list();
void place_order(object equipment);
string get_file(string name);
void does_accept(string response);
void finalize_order(int accept);
void inst_eq();
int order (string arg);
int certify (string arg);
void certify_list();

//GLOBAL VARIABLES
int accept;
object equipment;
mapping CertMap =(["fabricate":({"NONE", 10000, 6000}), 
                   "extract":({"NONE", 20000, 12000}), 
                   "purify":({"NONE", 25000, 18000}), 
                   "dismantle":({"NONE", 30000, 20000}), 
                   "hybridize":({"extract", 75000, 30000}), 
                   "agregate":({"purify", 100000, 45000}), 
                   "enhance":({"dismantle", 200000, 60000}), 
                   "infuse":({"hybridize", 250000, 75000})
                   ]);

void create()
{
    ::create();
    
    set_id(({"computer"}));
    set_short("white desktop computer");
    set_long ("You see a modern looking white desktop computer.\n"
              "There are three options on the screen\n"
              "construct <help construct>\n"
              "certify <help certify>\n"
              "order <help order>\n");
}

void init()
{
    add_action("order", "order");
    add_action("certify", "certify");
}

int prevent_get(){
    return 1;
}




int order (string arg){
    
    string fileName;
    arg = lower_case(arg);
    
    if ( !arg ){
        equipment_list();
        return 1;
    }
    
    fileName = get_file(arg);
    load_object(fileName);
    equipment = find_object(fileName);

    
    if (!equipment)
    {
        write("object not found\n");
        return 1;
    }
    
    if  (!is_a("/obj/research/equipment.c", equipment))
    {
        write("not equipment\n");
        return 1;
    }
    
    
    write ("This equpiment costs " + equipment->get_cost() + ", you have " + this_player()->get_cash()  + ".\n");
    
    if(this_player()->get_cash()< equipment->get_cost())
    {
        write("You can't afford that item!\n");
        return 1;
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
    equipString += "dismantling machine - Allows artifacts to be dismantled and examined\n";
    equipString += "cost:  $950,000     Certification required:  Dismantle \n";
    equipString += "Installation location: artifact vault \n\n";
    equipString += "Anti-slime hybridizer - Allows antislime to to mixed together\n";
    equipString += "cost:  $1,250,00     Certification required:  hybridize \n";
    equipString += "Installation location: slime annex \n\n";
    equipString += "Serum aggregator - Permits the mixing of serums\n";
    equipString += "cost:  $1,750,000     Certification required:  aggrigate \n";
    equipString += "Installation location: Liquid Laboratory \n\n";
    equipString += "Weapon enhancer - Allows weapons to be enhanced by components\n";
    equipString += "cost:  $2,000,000    Certification required:  enhance \n";
    equipString += "Installation location: artifact vault \n\n";
    equipString += "Anti-slime infuser - infuses uniforms with anti-slime or anti-slime mixtures.\n";
    equipString += "cost:  $6,000,000    Certification required:  infuse \n";
    equipString += "Installation location: slime annex \n\n";
    write (equipString);
    
}

void place_order(object equipment){
    
    write ("A burly delivery man clamers into the room and looks around. He \n"
           "says to " + this_player()->query_name() + " \"Did you order a "+ equipment->query_short() + "?\n"
           "If so, just say the word to ACCEPT it and I'll install it right away!\"\n");
    
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
        write ("The burly delivery man says \"Hey, building codes only allow me to place\n"
               "this in a " + equipment->get_location() + " annex.  Order again after you've had one built.\"\n");
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
           "\"All set there!\", as he leaves\n");
}





int certify(string arg){
    string *certifications;
    int tuition;
    int credits;
    
    arg = lower_case(arg);
    
    if ( !arg ){
        certify_list();
        return 1;
    }
    if (!CertMap[arg]){
        write ("That certification is not currently offered");
        return 1;
    }
    tuition = CertMap[arg][2];
    credits = CertMap[arg][3];
    
    write ("This Certificatin requires $" + tuition + " and " + credits + " research credits.");
    return 1;
}


void certify_list()
{
    string equipString;
    
    equipString = "================================[CERTIFICATIONS]================================\n\n";
    equipString += "Fabricate --- Tuition:  $10,000  +   6000 research hours   Prerequisites: NONE\n";
    equipString += "Extract ----- Tuition:  $20,000  + 12,000 research hours   Prerequisites: NONE\n";
    equipString += "Purify ------ Tuition:  $25,000  + 18,000 research hours   Prerequisites: NONE\n";
    equipString += "Dismantle --- Tuition:  $30,000  + 20,000 research hours   Prerequisites: NONE\n";
    equipString += "Hybridize --- Tuition:  $75,000  + 30,000 research hours   Prerequisites: extract\n";
    equipString += "Aggregate --- Tuition:  $100,000 + 45,000 research hours   Prerequisites: purify\n";
    equipString += "Enhance ----- Tuition:  $200,000 + 60,000 research hours   Prerequisites: dismantle\n";
    equipString += "Infuse ------ Tuition:  $250,000 + 75,000 research hours   Prerequisites: hybridize\n";
    equipString += "===============================================================================\n\n";
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
               "dismantler":"/obj/research/dismantler.c",
               "Dismantler":"/obj/research/dismantler.c",
               "dismantling machine":"/obj/research/dismantler.c",
               "Dismantling machine":"/obj/research/dismantler.c",
               "hybridizer":"/obj/research/hybridizer.c",
               "Hybridizer":"/obj/research/hybridizer.c",
               "anti-slime hybridizer":"/obj/research/hybridizer.c",
               "Anti-slime hybridizer":"/obj/research/hybridizer.c",
               "aggrigator":"/obj/research/aggrigator.c",
               "Aggrigator":"/obj/research/aggrigator.c",
               "serum aggrigator":"/obj/research/aggrigator.c",
               "Serum aggrigator":"/obj/research/aggrigator.c",
               "enhancer":"/obj/research/enhancer.c",
               "Enhancer":"/obj/research/enhancer.c",
               "weapon enhancer":"/obj/research/enhancer.c",
               "Weapon enhancer":"/obj/research/enhancer.c",
               "infuser":"/obj/research/infuser.c",
               "anti-slime infuser":"/obj/research/infuser.c",              
               ]);
    
    return objMap[name];
}




