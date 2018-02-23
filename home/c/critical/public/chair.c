inherit FURNITURE;

void create()
{
    set_id(({"chair"}));
    set_short("a chair");
    set_long("A comfortable looking chair.");
    set("prevent_get", 1);
    SetCurrentCapacity(0);
    SetMaxCapacity(1);
    CanSit();
}

int CanSit()
{
	return 1;
}