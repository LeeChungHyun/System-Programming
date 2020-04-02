#include <fcntl.h>
#include <stdio.h>

int main(int argc, char * argv[]){
    FILE *fpo;
    int fdo;

    if(argc != 2){
        perror(argv[0]);
        return 1;
    }
    if((fdo = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1){
        perror(argv[1]);
        return 1;
    }
    if((fdo = fdopen(fdo, "r+")) == NULL){
        perror("fdopen");
        return 2;
    }
    fprintf(fpo, "Hello, world! \n");
    fclose(fpo);
}