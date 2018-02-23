inherit OBJECT;

int select(string num);
int radio( string msg);
int getchannel();
void setchannel(int num);
int getchannels();
void setchannels(int num);

int channel=1;
int channels=64;

void create()
{
	::create();
    set_id(({"radio", "walkie", "talkie","Talkie" , "Walkie", "Radio"}));
    set_short("Hand Held Radio");
    set_long("A small hand held radio that has simple channel selector ([SELECT] <channel>)\nalong with a side button to transmit ([RADIO] <message>)");
    setValue(20000);
}

void init()
{
	add_action("radio","radio");
	add_action("select","select");	
}

int radio( string msg )
{
	object *radios;
	
	
	if(!msg)
	{
		write("SYNTAX: Radio <msg>");
		return 1;
	}
	
	radios=children("/obj/gadgets/handradio.c");
	
    tell_room(environment(this_player()),this_player()->query_cap_name() + " holds down the transmit button and sayes,\"" + msg + "\"\n",this_player());
    write("Radio <"+channel+"> "+ this_player()->query_cap_name()+ "<-> " + msg + "\n");
	for(int i=0; i < sizeof(radios); i++)
	{
        if( !environment(radios[i]) ) continue;
		if(radios[i]->getchannel()==getchannel() && radios[i] != this_object() )
		{				
			tell_room(environment(environment(radios[i])),"Radio <"+channel+"> "+ this_player()->query_cap_name()+ " <-> " + msg + "\n", this_player());
		}	
		
	}
	
	
	
	return 1;
	
}


int select(string num)
{
int chan;
    
	if(!num)
	{
		write("SYNTAX: select <channel number>\n");
		return 1;
	}
    chan=to_int(num);
    
    if(chan <= 0)
    {
        write("The channel must be a postive number and not zero.\n");
        return 1;
    }
    
	if(chan < 65)
	{
		write("You change your radio's channel to " + chan + "\n");
		setchannel(chan);
		return 1;
	}
	else
	{
		write("This radio only has 64 channels!\n");
		return 1;
	}
}

int getchannel()
{
	return channel;
}

void setchannel(int num)
{
	channel=num;
}

int getchannels()
{
    return channels;
}

void setchannels(int num)
{
    channels=num;
}
    