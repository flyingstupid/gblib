inherit ROOM;

void create()
{
    set_light(1);
    set_ghost_ok(1:);
}

void add_co_exit(string exit, int x, int y )
{
    string exitPath;

    exitPath = "co_" + x +"_" + y;

    exits[exit] = exitPath;
}
