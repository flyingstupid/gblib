inherit COMMAND;

#define SLIMER  "/home/c/critical/public/slimer.c"
#define DEMO1 "/areas/demo/demo1.c"
#define DEMO2 "/areas/demo/demo2.c"
#define DEMO3 "/areas/demo/demo3.c"
#define DEMO4 "/areas/demo/demo4.c"
#define DEMO5 "/areas/demo/demo5.c"

string *demoRooms = ({ DEMO2, DEMO3, DEMO4, DEMO5 });

int main( string arg )
{
    object ob;
    int a;
    ob = clone_object( SLIMER  );
    a = random( 4 );
             
    if( ob )
    {
        load_object( demoRooms[a] );
        ob->move( demoRooms[a] );
    }

    write("Ghost Combat Demo started!\n");
    return 1;	
}
