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
#define BSIZE2 524288000
//#define BSIZE2 100

int main(int argc, char *argv[]){
    if(argc != 4){
        cerr << "Usar: " << argv[0] <<"archivo1 archivo2 archivo3" << endl;
        return -1;
    }

    ssize_t bytes;
    char buffer[BSIZE];
    bool f  = 1;
    int i = 0;
    char *c;
    char seq[10] = "\x75\x6e\x69\x66\x63";

    long long size_2 = BSIZE2;
    /*FILE 1*/
    int fd_out = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd_out < 0){
        perror(argv[1]);
        return -1;
    }

    if(ftruncate(fd_out, size_2) < 0){
        perror("Error fijando tamaño del archivo de salida");
        return -1;
    }

    void *addr_out = mmap(0, size_2, PROT_WRITE, MAP_SHARED, fd_out, 0);
    if(addr_out == MAP_FAILED){
        perror("Error mapeando archivo de salida");
        return -1;
    }
    
    /*FILE 2*/
    int fd_out1 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd_out1 < 0){
        perror(argv[2]);
        return -1;
    }

    if(ftruncate(fd_out1, size_2) < 0){
        perror("Error fijando tamaño del archivo de salida");
        return -1;
    }

    void *addr_out1 = mmap(0, size_2, PROT_WRITE, MAP_SHARED, fd_out1, 0);
    if(addr_out1 == MAP_FAILED){
        perror("Error mapeando archivo de salida");
        return -1;
    }
    /*FILE 3*/
    int fd_out2 = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd_out2 < 0){
        perror(argv[3]);
        return -1;
    }

    if(ftruncate(fd_out2, size_2) < 0){
        perror("Error fijando tamaño del archivo de salida");
        return -1;
    }

    void *addr_out2 = mmap(0, size_2, PROT_WRITE, MAP_SHARED, fd_out2, 0);
    if(addr_out2 == MAP_FAILED){
        perror("Error mapeando archivo de salida");
        return -1;
    }    

    c = (char*)addr_out;
    sprintf(c , "%s", seq);

    c = (char*)addr_out1;
    sprintf((c + (long long)(BSIZE2)/2 - 5), "%s", seq);

    c = (char*)addr_out2    ;
    sprintf((c + (long long)(BSIZE2) - 6), "%s", seq);

    close(fd_out);
    close(fd_out1);
    close(fd_out2);

    return 0;
}
