#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    FILE *fp;

    //Inicio
    fp = fopen("bigfakefile1.txt","w");

    // fprintf(fp, "%s\n", "75 6e 69 66 63"); 
    for(i=0;i<(500);i++) {    
        fseek(fp,(1024*1024),SEEK_CUR);    
        if (i == 200){
            fprintf(fp, "75 6e 69 66 63");  
            continue;
        }
        
        
        fprintf(fp,"C");
    }
    // fprintf(fp, "%s\n", "hola");
    
    fclose(fp);

    //medio
    fp = fopen("bigfakefile2.txt","w");
    for(i=0;i<(500);i++) {
        if (i == 300){
        	fprintf(fp, "75 6e 69 66 63");	
            continue;
        }   
        fseek(fp,(1024*1024),SEEK_CUR); 
        fprintf(fp,"C");
    }
    fclose(fp);
    
    //final
    fp = fopen("bigfakefile3.txt","w");
    for(i=0;i<(500);i++) {
        fseek(fp,(1024*1024),SEEK_CUR);
        fprintf(fp,"C");
    }
    fprintf(fp, "75 6e 69 66 63");
    fclose(fp);

    return 0;
}
