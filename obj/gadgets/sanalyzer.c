inherit OBJECT;


void create()
{
    set_id(({"spectral", "analyzer", "Spectral" , "Analyzer", "Spectral Analyzer"}));
    set_short("A Spectral Analyzer");
    set_long( "A large metal domed helmet connected via many unshielded wires\n"
		"to a laptop. The image is of drastic rainbow patterns that has\n"
		"a spooky shadowy image.\n");
}


analyze(string target)
{
    object target;
    target=find_living(target);
    if(!target)
    {
     write("You must use this device on a target!");    
    }
    
    
    
    write(image);
}


return 1;
}







