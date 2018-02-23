inherit FURNITURE;

void create()
{
    set_id(({"furniture"}));
    set_short("some furniture.");
    set_long("Some furniture.");
    //set("prevent_get", 1);
}

int CanSit()
{
	return 1;
}