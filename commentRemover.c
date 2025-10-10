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

bool successfully_get_file_extension(char *filename, char *fileExtension){
    char* extensionSeparatorIndex = strrchr(filename, '.');

    if(extensionSeparatorIndex == NULL){
        return false;
    }else{
        strcpy(fileExtension,extensionSeparatorIndex+1);
        return true;
    }
}

bool detect_single_line_comment (int character, FILE* fileReadPtr){
    if(character == '/'){
        int nextCharacter = fgetc(fileReadPtr);
        if(nextCharacter == '/'){
                return true;
        } else {
            ungetc(nextCharacter, fileReadPtr);
            return false;
        }
    }
    return false;
}

void string_literal_detector(int character, int previousCharacter, bool* toggle){
    if(character == '"' && previousCharacter != '\\'){
        if((*toggle) == true){
            (*toggle) = false;
        }else{
            (*toggle) = true;
        }
    }
}

void write_to_new_file_without_comments(FILE* fileReadPtr, FILE* fileWritePtr){
    int character;
    int characterSnapshot = 0;
    bool toggle = false;

    while ((character = fgetc(fileReadPtr)) != EOF) {
        string_literal_detector(character, characterSnapshot, &toggle);

        if(toggle){
            fputc(character, fileWritePtr);
        }else if(detect_single_line_comment(character, fileReadPtr)){

            while ( character != EOF && character !='\n'){
                character = fgetc(fileReadPtr);
            }

            if(character == '\n'){
                fputc('\n', fileWritePtr);
            }
        }else{
            fputc(character, fileWritePtr);
        }
        
        characterSnapshot = character;
    }
}

int main(int argc , char* argv[]){

    if(!is_input_file_provided(argc)){
        fprintf(stderr, "no input file is provided\nUsage: %s <filename>\n",argv[0]);
        return 1;
    }

    if(filename_too_long(argv[1])==true){
        fprintf(stderr, "Error: filename too long (max %d chars)\n",MAX_FILENAME_LENGTH);
        return 1;
    }

    char filename[MAX_FILENAME_LENGTH];
    strcpy(filename, argv[1]);
    char fileExtension[10];

    FILE* fileReadPtr = fopen(filename, "r");
    FILE* fileWritePtr = fopen("output.txt", "w");
    
    if(successfully_get_file_extension(filename, fileExtension) == false){
        fprintf(stderr, "Invalid filename: File name must include a valid extension (e.g., .py, .c, .js)\n");
        return 1;
    }
    
    if(fileReadPtr == NULL || fileWritePtr == NULL){
        perror("Error opening file");
        return 1;
    }


    write_to_new_file_without_comments(fileReadPtr,fileWritePtr);

    fclose(fileReadPtr);
    fclose(fileWritePtr);
    
    return 0;
}
