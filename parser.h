/* START Header Guard */
#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdio.h>

typedef struct instruction_struct{
    char** tokens; 
    int numTokens;
} Instruction;

/* Parses string and initializes the Instruction structure */
Instruction parseInstructionString(char*);

/* Checks if a instruction is a valid MUCKS instruction. 
 * TRUE - Instruction is valid MUCK instruction
 * FALSE - Display compile error to console and return false. */
bool isValidInstruction(Instruction);

/* Parses string and initializes the Instruction structure */
char* readLine(FILE* fp);


#endif /* END PARSER.H HEADER GUARD*/

