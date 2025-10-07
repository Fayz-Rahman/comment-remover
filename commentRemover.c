#include<stdio.h>
#include<stdlib.h>
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

void get_file_extension(char *filename, char *fileExtension){
    char* extensionSeparatorIndex = strrchr(filename, '.');

    if(extensionSeparatorIndex == NULL){
        printf("Invalid filename: File name must include a valid extension (e.g., .py, .c, .js)\n");
        exit(1);
    }else{
        strcpy(fileExtension,extensionSeparatorIndex+1);
    }
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
    char fileExtension[10];
    get_file_extension(filename, fileExtension);

    // printf("%s\n",fileExtension);
    // printf("%s\n",filename);
    
    return 0;
}
