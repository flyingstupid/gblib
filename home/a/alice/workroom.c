inherit ROOM;
void create()
{
    set_light(1);
    set_short("A workroom");
    set_long(
         "This is the workroom of a madman. The walls are covered with charcoal drawings\n"
         "of rooms, buildings, and symbols. The faded wallpaper can be seen peaking\n"
		 "between the tattered papers. The desk is filled with model designs sitting\n"
		 "on top of their corresponding blueprints.\n"
     );
    set_exits( ([
         "cafe" : "/areas/lpuni/entrance.c",
         "void" : "/areas/std/void.c"
     ]) );
    set_items( ([
         "walls" : "Looking closer at the walls, you see they are covered in charcoal scrawlings.\n",
         "symbols" : "Little oddities, nothing special. Until you settle on one large symbol.\n"
              "The room begins to spin and turn and twist until you break eye contact.\n",
         "model" : "Small scale models made of sculpting clay sit on an old desk. What may\n"
              "have once been detailed sculptures have been attacked with a knife. The \n"
              "offending tool rests buried to its hilt in a miniature hospital wing.\n",
		 "scrawlings" : "The words 'Remove the head, it's still not dead' are repeated nearly\n"
              "endless across the room. Over and over again...\n",
    ]) );
}
