mixed clamp( mixed v, mixed a, mixed b )
{
    if( v < a )
        return a;
    else if( v > b )
        return b;

    return v;
}


