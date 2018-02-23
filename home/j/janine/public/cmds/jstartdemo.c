inherit COMMAND;

#define SLIMER  "/home/j/janine/public/slimer.c"
#define DEMO1 "/areas/demo/demo1.c"
#define DEMO2 "/areas/demo/demo2.c"
#define DEMO3 "/areas/demo/demo3.c"
#define DEMO4 "/areas/demo/demo4.c"
#define DEMO5 "/areas/demo/demo5.c"

int main( string arg )
{
    object ob;
    ob = clone_object( SLIMER  );
             
    if( ob )
    {
        load_object( DEMO2 );
        ob->move( DEMO2 );
    }
    return 1;	
}
