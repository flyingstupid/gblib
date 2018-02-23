inherit ROOM;

object doc;

void create()
{
     set_light(1);
     set_short("Hospital - Emergency Room");
     set_long("Plain cream colored walls stand in the four corners of this room. A medical bed attatches to the wall through handfuls of wires, tubes and connections. Various machines around you beep, chirp and sound  off. A freshly cleaned and sterialized smell almost overwhelms you.");
     
     
     
     set_exits( ([ "streets" : ({"/areas/street.c"}), ]) );
     doc=clone_object("areas/hospital/mobiles/ERDoctor.c");
     doc->move("areas/hospital/hospitalER.c");
}
