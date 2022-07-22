#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

#define bufSize 1024

/* Parses string and initializes the Instruction structure */
Instruction parseInstructionString(char* instructionString){

   Instruction instruction;
   const char s[2] = " ";
   char *token = NULL;
   
   // Get first token (before space).
   char** tokens;
   token = strtok(instructionString, s); 
   tokens = malloc(sizeof(char*));
   tokens[0] = (char *) malloc(strlen(token)+1);
   strcpy(tokens[0], token);
   tokens[0][strlen(token)] = '\0'; 
   int numTokens = 1;
   
   if (tokens[0] == NULL){
       printf("ERROR - No Tokens!\n");
       return instruction;
   }
   
   // walk through other tokens 
   while( token != NULL ) {
        token = strtok(NULL, s);
        if (token != NULL){     
            if (strlen(token) == 1 && token[0] == ' ')
                continue;
              
            tokens = realloc(tokens, sizeof(char*) * (numTokens+1) );
            tokens[numTokens] = (char *) malloc(strlen(token)+1);
            strcpy(tokens[numTokens], token); 
            (numTokens)++;  
        }
      
    }  

    //remove any \n characters in tokens
    for(int i=0;i<numTokens;i++){
        for(int k=0;k<strlen(tokens[i]);k++){
            if (tokens[i][k] == '\n'){
                tokens[i][k] = '\0';
            } 
        }
    }
   
    instruction.tokens = tokens;
    instruction.numTokens = numTokens;
   
    return instruction; 
}

/* Checks if a instruction is a valid MUCKS instruction. 
 * TRUE - Instruction is valid MUCK instruction
 * FALSE - Display compile error to console and return false. */
bool isValidInstruction(Instruction instruction){
    
    if (instruction.numTokens < 3){
        fprintf(stderr, "COMPILE ERROR - Error Code #1:  Incorrect number of tokens: %d\n", instruction.numTokens);
        return false;
    }
    else if ((instruction.numTokens % 2) == 0){
        fprintf(stderr, "COMPILE ERROR - Error Code #2:  Incorrect number of tokens: %d\n", instruction.numTokens);
        return false;
    }
    else if (instruction.tokens[1][0] != '='){
        fprintf(stderr, "COMPILE ERROR - Error Code #3: Second token not is not = operator\n");
        return false;
    }
    else if (strlen(instruction.tokens[0]) != 1){
        fprintf(stderr, "COMPILE ERROR - Error Code #4: Invalid assignment!  First token %s is not a valid variable\n", instruction.tokens[0]);
        return false;
    }
    
    int ascii = (int) instruction.tokens[0][0];
    if (ascii < 97 || ascii > 122){
        fprintf(stderr, "COMPILE ERROR - Error Code #5: Assignment variable (1st token) must be a through z\n");
        return false;
    }
    
    //Check Operators must be either + or -
    for(int i=3;i<instruction.numTokens;i=i+2){
        if (strlen(instruction.tokens[i]) != 1){
            fprintf(stderr, "COMPILE ERROR - Error Code #6: Invalid operators %s, must be + or - \n", instruction.tokens[i]);
            return false;
        }
        else if (instruction.tokens[i][0] != '+' && instruction.tokens[i][0] != '-'){
            fprintf(stderr, "COMPILE ERROR - Error Code #7: Invalid operators %s, must be + or - \n", instruction.tokens[i]);
            return false;
        }
    }
    
    //check for number or variable
    for(int i=2;i<instruction.numTokens;i=i+2){
        
        if(strlen(instruction.tokens[i]) == 1){
            ascii = instruction.tokens[i][0];
            if ( !( (ascii >= 'a' && ascii <= 'z') || (ascii >= '0' && ascii <= '9')) ){
                fprintf(stderr, "COMPILE ERROR - Error Code #8: Token %s, is not a variable or number \n", instruction.tokens[i]);
                return false;
            }
        }
        else{
            // If string length is more then one character long, then check if a number
            for(int k=0;k<strlen(instruction.tokens[i]);k++){
                ascii = instruction.tokens[i][k];
                if (ascii < '0' || ascii > '9'){
                    fprintf(stderr, "COMPILE ERROR - Error Code #9: Token |%s|, is not a variable or number \n", instruction.tokens[i]);
                    return false;
                }
            }
        }
    }
    return true;
}

/* Read a single line from a file.  Return line read as a string on heap */
char* readLine(FILE* fp){
    char buf[bufSize];
    if (fgets(buf, sizeof(buf), fp) != NULL)
    {
        buf[strlen(buf) - 1] = '\0'; // eat the newline fgets() stores
        char* str = malloc(strlen(buf));
        
        //Copy String character by character
        int i;
        for(i=0;i<strlen(buf);i++){
            str[i] = buf[i];
        }
        str[i] = '\0';
        
        return str;
    }
    return NULL;
}
