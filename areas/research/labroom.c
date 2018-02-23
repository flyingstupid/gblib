//
//  /areas/research/labroom.c
//  GB Mud
//


inherit ROOM;
inherit COMMAND;


//FUNCTION PROTOTYPES
void add_equip(string newEquip);
int get_equip(string getEquip);
void equipment_list();
void place_order();
string get_file(string name);
void does_accept(string response);
void finalize_order(int accept);
void inst_eq();
int order (string arg);
int certify (string arg);
void certify_list();
void make_tube();
void make_vial();
void make_bag();


//GLOBAL VARIABLES
int accept;
string equip;
int fab;
string *equipmentArray = ({});
mapping CertMap =(["fabricate":({"NONE", 10000, 6000}), 
                   "extract":({"NONE", 20000, 12000}), 
                   "purify":({"NONE", 25000, 18000}), 
                   "dismantle":({"NONE", 30000, 20000}), 
                   "hybridize":({"extract", 75000, 30000}), 
                   "agregate":({"purify", 100000, 45000}), 
                   "enhance":({"dismantle", 200000, 60000}), 
                   "infuse":({"hybridize", 250000, 75000})
                   ]);

mapping EquipMap = (["fabricator":({"A fabricting machine sits on one of the lab benches", 300000, "lab","A large metal machine with three blinking buttons one the top." }),
                     "extractor":({"A slime extractor hums softly next to a fume hood", 400000, "slime", "A large stainless steel machine with lots of tubes and slots"}),
                     "purifier":({"A purifying maching sits next to a granite sink", 550000, "liquid", "A glass and plastic machine with a narrow funnel at the top"}),
                      "dismantler":({"A filthy dismantling maching sits in one corner", 950000, "artifact", "An enormous granite block with a large hammer attached by a chain"}),
                     "hybridizer" :({"A hybridizing machine is sitting on a work bench", 1250000, "slime", "A large stainless steel machine with lots of tubes and slots" }),
                     "aggregator" :({"A serum aggregator putters away in a corner", 1750000, "liquid", "a big metalic machine with lots of vials and condensation tubes"}),
                    "enhancer" :({"A bench used for weapons enhancement is located along the back wall", 2000000, "artifact", "a bench with a vice and several small tools scattered over the top"}),
                     "infuser" :({"An antislime infuser rests in the fume hood", 6000000, "slime", "a very large pressing machine with a space for a vila of anti-slime"}),
                     ]);

                     

void create()
{
    ::create();
    
    set_light(1);
    set_short("Lab");
    set_long(
             "This stark white lab is immaculate and well lit.\n"
             "There are several lab benchs and stools scattered about the\n"
             "area.  A giant white board is attached to one wall and an assortment\n"
             "of colored markers can be found on a shelf just below.\n\n"
             "There is a white desktop computer here.\n"
             );
    set_items( ([
                 "computer" : "You see a modern looking white desktop computer.\n"
                 "There are two options on the screen\n"
                 "[certify] (skill)\n"
                 "[order] (equipment)\n",
                 "computer" : "You see a modern looking white desktop computer.\n"
                 "There are two options on the screen\n"
                 "[certify] (skill)\n"
                 "[order] (equipment)\n",
                 ]) );   
    
}

void init()
{
    add_action("order", "order");
    add_action("certify", "certify");
    add_action("fabricate", "fabricate");
}


void add_equip(string newEquip)
{
    equipmentArray += ({ newEquip });
}

int get_equip(string getEquip)
{
    int foundIndex;
    
    foundIndex = member_array( getEquip, equipmentArray );
    if (foundIndex == -1){
        return 0;
    }
    return 1;
}


/*-----------------------------------------------------------------------
 --------------------------  ORDER FUNCTIONS  ---------------------------
 ------------------------------------------------------------------------*/


int order (string arg){
    
    if ( !arg )
    {
        equipment_list();
        return 1;
    }
    if (!EquipMap[arg])
    {
        write("That item is out of stock\n");
        return 1;
    }
    
    equip = arg;
    
    write ("This equpiment costs " + EquipMap[equip][1] + ", you have " + this_player()->get_cash()  + ".\n");
    
    if(this_player()->get_cash()< EquipMap[equip][1])
    {
        write("You can't afford that item!\n");
        return 1;
    }
    
    tell_object (this_player(), "Your order has been placed, expect delivery shortly.\n");
    call_out ("place_order", 5);
    
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

void place_order(){
    
    write ("A burly delivery man clamers into the room and looks around. He \n"
           "says to " + this_player()->query_name() + " \"Did you order a "+ equip + "?\n"
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
    
    if ((equip == "fabricating machine" || equip == "fabricator" ) && is_a ("/areas/research/labroom.c", environment(this_player())))
    {
        inst_eq();
        return; 
    }
    
    if (!environment(this_player())->query_exit(EquipMap[equip][2]))
    {
        write ("The burly delivery man says \"Hey, building codes only allow me to place\n"
               "this in a " + EquipMap[equip][2] + " annex.  Order again after you've had one built.\"\n");
        return;
    }
    inst_eq();
    return;    
}


void inst_eq(){
    string locationName;
    object location;
    string old_long, new_long;
    
    if (equip == "fabricator")
    {
        location = environment(this_player());
    }
    
    else
    {
        locationName = (environment(this_player())->query_exit(EquipMap[equip][2]));
        load_object(locationName);
        location = find_object(locationName);
    }
    old_long = location->query_long();
    new_long = old_long +"\n\n" +  EquipMap[equip][0];
    location->set_long(new_long);
    location->add_item(EquipMap[equip], EquipMap[equip][0]);
    location->add_equip(equip);
    
    this_player()->set_cash(this_player()->get_cash() - EquipMap[equip][1]);
    
    write ("The delivery man tips his cap in " +this_player()->query_short() + "'s direction and says\n"
           "\"All set there!\", as he leaves\n");
}


/*-----------------------------------------------------------------------
 --------------------------  CERTIFY FUNCTIONS --------------------------
 ------------------------------------------------------------------------*/

int certify (string arg){
    int tuition;
    int credits;
    
    
    
    if ( !arg ){
        certify_list();
        return 1;
    }
    
    arg = lower_case(arg);
    
    if (!CertMap[arg]){
        write ("That certification is not currently offered\n");
        return 1;
    }
    tuition = CertMap[arg][1];
    credits = CertMap[arg][2];
    
    if (this_player()->GetResearchCurrent() < credits)
    {
        write("You don't have enough research credit for that certification.\n");
        return 1;
    }
    
    if (this_player()->get_cash() < tuition)
    {
        write("You can't afford that certification.\n");
        return 1;
    }
    if (this_player()->get_skill(arg))
    {
        write("You are already certified in that technique.\n");
        return 1;       
    }
    if ((CertMap[arg][0] != "NONE") && (!this_player()->get_skill(CertMap[arg][0])))
    {
        write("You have not completed the prerequisite certifications.\n");
        return 1;
    }
    
    this_player()->set_skill(arg, 1);
    this_player()->SetResearchCurrent(this_player()->GetResearchCurrent() - credits);
    this_player()->set_cash(this_player()->get_cash() - (tuition* 100));
    
    
    
    write ("You have been certified in " + arg + " $" + tuition + " and " + credits + " research credits have been removed from your account.\n");
    return 1;
}


void certify_list()
{
    string certString;
    
    certString = "================================[CERTIFICATIONS]================================\n\n";
    certString += "Fabricate --- Tuition:  $10,000  +   6000 research hours   Prerequisites: NONE\n";
    certString += "Extract ----- Tuition:  $20,000  + 12,000 research hours   Prerequisites: NONE\n";
    certString += "Purify ------ Tuition:  $25,000  + 18,000 research hours   Prerequisites: NONE\n";
    certString += "Dismantle --- Tuition:  $30,000  + 20,000 research hours   Prerequisites: NONE\n";
    certString += "Hybridize --- Tuition:  $75,000  + 30,000 research hours   Prerequisites: extract\n";
    certString += "Aggregate --- Tuition:  $100,000 + 45,000 research hours   Prerequisites: purify\n";
    certString += "Enhance ----- Tuition:  $200,000 + 60,000 research hours   Prerequisites: dismantle\n";
    certString += "Infuse ------ Tuition:  $250,000 + 75,000 research hours   Prerequisites: hybridize\n";
    certString += "===============================================================================\n\n";
    write (certString);
    
}



/*-----------------------------------------------------------------------
 ------------------------  FABRICATE FUNCTIONS --------------------------
 ------------------------------------------------------------------------*/


int fabricate (string arg){
    
    if (!get_equip("fabricator"))
    {
        return(notify_fail("Your lab is not equiped to fabricate items.\n"));
    }
    
    if (!this_player()->get_skill("fabricate"))
    {
        return(notify_fail("You are not certified to use this equipment.\n"));
    }
    
    if (!arg)
    {
        return(notify_fail("You need to specify what sort of item to fabricate.\n Example: fabricate Test tube \n "));
    }
    
    if (arg == "tube" || arg == "test tube" || arg == "Test Tube" || arg == "Test Tube")
    {
        tell_object(this_player(), "You begin to fabricate a test tube.\n");
        call_out("make_tube", 10);
    }
    
    if (arg == "Vial" || arg == "vial" || arg == "Glass vial" || arg == "glass vial")
    {
        tell_object(this_player(), "You begin to fabricate a glass vial.\n");
        call_out("make_vial", 15);
    }
    
    if (arg == "bag" || arg == "Sample Bag" || arg == "samble bag" || arg == "Sample bag")
    {
        tell_object(this_player(), "You begin to fabricate a sample bag.\n");
        call_out("make_bag", 20);
    }
    
    return 1;
    
}

int query_wait_time( string arg ){
    return 1500;
}

void make_tube()
{
    int test;
    object newTube;
    
    test = this_player()->DoSkillRoll("fabricate", 5);
    
    if (test > 0)
    {
        tell_object(this_player(), "You successfully fabricate a test tube.\n");
        newTube= clone_object("/obj/research/tube.c");
        newTube->move(this_player());
    }
    else
    {
        tell_object(this_player(), "You lose concentration and fail to fabricate a test tube.\n");
    }
    return;
}


void make_vial()
{
    int test;
    object newVial;
    
    test = this_player()->DoSkillRoll("fabricate", 15);
    
    if (test > 0)
    {
        tell_object(this_player(), "You successfully fabricate a glass vial.\n");
        newVial= clone_object("/obj/research/vial.c");
        newVial->move(this_player());
    }
    else
    {
        tell_object(this_player(), "You lose concentration and fail to fabricate a glass vial.\n");
    }
    return;
}


void make_bag(){
    int test;
    object newBag;
    
    test = this_player()->DoSkillRoll("fabricate", 25);
    
    if (test > 0)
    {
        tell_object(this_player(), "You successfully fabricate a sample bag.\n");
        newBag= clone_object("/obj/research/tube.c");
        newBag->move(this_player());
    }
    else
    {
        tell_object(this_player(), "You lose concentration and fail to fabricate a sample bag.\n");
    }
    return;
}



