
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_FILENAME_LENGTH 255 


bool is_input_file_provided(int argc){
    if(argc<2){
        return false;
    }

    return true;
}

bool filename_too_long (char* filename){
    size_t length_of_filename_input = strlen(filename);

    if(length_of_filename_input > MAX_FILENAME_LENGTH){
        return true;
    }

    return false;
}



int main(int argc , char* argv[]){

    if(!is_input_file_provided(argc)){
        printf("no input file is provided\nUsage: %s <filename>\n",argv[0]);
        return 1;
    }

    if(filename_too_long(argv[1])==true){
        printf("Error: filename too long (max %d chars)\n",MAX_FILENAME_LENGTH);
        return 1;
    }

    char filename[MAX_FILENAME_LENGTH];
    strcpy(filename, argv[1]);

    // printf("%s\n",filename);
    return 0;
}
