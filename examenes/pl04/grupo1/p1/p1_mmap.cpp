#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
using namespace std;

#define BSIZE 1024

int main(int argc, char *argv[]){
    if(argc != 2){
        cerr << "Usar: " << argv[0] <<"archivoingreso" << endl;
        return -1;
    }

    int fd_in = open(argv[1], O_RDONLY);
    if(fd_in < 0){
        perror(argv[1]);
        return -1;
    }

    struct stat info;
    if(fstat(fd_in, &info) < 0){
        perror("Error status de archivo de ingreso");
        return -1;
    }

    void *addr_in = mmap(0, info.st_size, PROT_READ, MAP_SHARED, fd_in, 0);
    if(addr_in == MAP_FAILED){
        perror("Error mapeando archivo de ingreso");
        return -1;
    }

    char seq[10] = "\x75\x6e\x69\x66\x63";
    int t = 0;
    bool f2 = 0;
    char *c= (char *)addr_in;
    while(t < info.st_size)
    {
        f2 = 1;
        for(int j=0, k=t; j<5; j++, k++)
        {
            if(c[k] != seq[j])
            {
                f2 = 0;     
                break;
            }
        }
        if(f2) break;
        t++;
    }
    cout << "MMAP: " << (f2?"YES":"NO") << endl;

    close(fd_in);

    return 0;
}
