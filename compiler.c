#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "compiler.h"

char regs[16] = "               ";

bool isNum(char* str){
    int i=0;
    
    while(str[i] != '\0'){
        if(isdigit(str[i]) == 0){
            return false;
        }
        else{
            return true;
        }
        i++;
    }
}
int setReg(char c){
    for(int i=0; i<16; i++){
        if(regs[i] == ' '){
           regs[i] = c;
           return i;
        }
    }
    return -1;
}
int getReg(char c){
    for(int i=0; i<16; i++){
        if(regs[i] == c){
            return i;
        } 
    }
    return -1;
}

