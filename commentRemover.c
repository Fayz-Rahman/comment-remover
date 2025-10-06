#include<stdio.h>
#include<stdbool.h>


bool is_input_file_provided(int argc){
    if(argc<2){
        return false;
    }

    return true;
}



int main(int argc , char* argv[]){

    if(!is_input_file_provided(argc)){
        printf("no input file is provided\nUsage: %s <filename>\n",argv[0]);
        return 1;
    }



    return 0;
}
