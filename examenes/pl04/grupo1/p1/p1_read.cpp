#include <iostream>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main( int argc, char* argv[] )
{
    FILE *fp;
    char *hist;
    int  len, pos=0, hl=0, i;
    char c;
    char find[] = {'\x75', '\x6e', '\x69', '\x66', '\x63'};

    fp = fopen( argv[1], "r" );
    len = (int)strlen( find );
    hist = (char*)malloc(len);
    memset( hist, 0, len );
    cout << "FOPEN: ";
    while ( !feof( fp )) {
        c = fgetc( fp );
        if ( find[pos++] == c ) {
            if ( pos == len ) {
                printf( "YES\n" );
                return 1;
            }
        }
        else {
            if ( pos > 0 ) {
                pos = 0;
                for ( i = 0; i < len - 1; i++ )
                    if ( 0 == memcmp( hist+len-i-1, find, i + 1 )) {
                    pos = i;
                }
            }
        }
        memmove( hist, hist + 1, len - 1 );
        hist[len-1] = c;
    }
    printf( "NO\n" );
}
