#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "compiler.h"

#define MAX_LIMIT 30

//Function Prototypes
void clean(Instruction instruction);
void printInstruction(Instruction instruction);


int main() {
    
    char filename[64];
    printf("Enter Source File Name: ");
    scanf("%s", filename );
    
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("ERROR opening file: %s!\n", filename);
        return EXIT_FAILURE;
    }
    
    int lineNumber = 1;
    char* str = readLine(f);
    while( str != NULL ){
        
        // Instruction string converted to Instruction Structure
        Instruction instruction = parseInstructionString(str);
       
        
        // Check if instruction is a valid MUCKS instruction
        bool isValid = isValidInstruction(instruction);    
        if (isValid == false){
            fprintf(stderr, "COMPILE ERROR: Line #%d, %s \n", lineNumber, str);
            return EXIT_FAILURE;
        }
        
        if(instruction.numTokens == 3){
            if(isNum(instruction.tokens[2])){
                int reg = 0;
                
                if(getReg(instruction.tokens[0][0]) == -1){
                    reg = setReg(instruction.tokens[0][0]);
                }
                else{
                    reg = getReg(instruction.tokens[0][0]);
                }
                printf("MOV R%d, #%s\n", reg, instruction.tokens[2]);
            }
        }
        if(instruction.numTokens == 5){
            if(!isNum(instruction.tokens[4])){
                int reg = 0;
                int reg2 = 0;
                int reg3 = 0;
                 
                if(getReg(instruction.tokens[0][0]) == -1){
                    reg = setReg(instruction.tokens[0][0]);
                }
                else if(getReg(instruction.tokens[0][0]) != -1){
                    reg = getReg(instruction.tokens[0][0]);
                }
                
                reg2 = getReg(instruction.tokens[2][0]);
                reg3 = getReg(instruction.tokens[4][0]);
                
                if(strcmp(instruction.tokens[3], "+") == 0){
                    printf("ADD R%d, R%d, R%d\n", reg, reg2, reg3);
                }  
                else if(strcmp(instruction.tokens[3], "-") == 0){
                    printf("SUB R%d, R%d, R%d\n", reg, reg2, reg3);
                }
            }
            else if(isNum(instruction.tokens[4])){
                int reg = 0;
                int reg2 = 0;
                
                if(getReg(instruction.tokens[0][0]) == -1){
                    reg = setReg(instruction.tokens[0][0]);
                }
                else{
                    reg = getReg(instruction.tokens[0][0]);
                }
                
                reg2 = getReg(instruction.tokens[2][0]);
                
                if(strcmp(instruction.tokens[3], "+") == 0){
                    printf("ADD R%d, R%d, #%s\n", reg, reg2, instruction.tokens[4]);
                }  
                else if(strcmp(instruction.tokens[3], "-") == 0){
                    printf("SUB R%d, R%d, #%s\n", reg, reg2, instruction.tokens[4]);
                }
            }
        }
        
   
		 // For each Instruction Structure, print each instruction tokens 
		 // to the screen.  You'll want to remove this, but it's included 
		 // in the template to demonstrate the functionality of the provided
		 // code template.
//        printf("Instruction #%d:\n", lineNumber);
		// printInstruction(instruction);
        
        lineNumber++;
        str = readLine(f); // Get Next Line from file
        clean(instruction); // Free Heap Memory used for instruction
    }
    fclose(f);
    
    return (EXIT_SUCCESS);
}

/* Print Instruction Tokens */ 
void printInstruction(Instruction instruction){
	for(int i=0;i<instruction.numTokens;i++){
		printf("  token[%d]: %s\n", i, instruction.tokens[i]);
	}
}


/* Frees memory allocated on the heap */
void clean(Instruction instruction){
    //Clean Up Heap Memory
    for(int i=0;i<instruction.numTokens;i++){
        free(instruction.tokens[i]);
    }
    free( instruction.tokens );
}
