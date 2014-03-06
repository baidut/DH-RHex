
#ifndef _AS5040_H_INCLUDE
#define _AS5040_H_INCLUDE

#include "_interface.h"

typedef struct
{
	GPIO CLK;
	GPIO DO;
	GPIO CS;
} AS5040; 

void 	AS_Init		(const AS5040* );
uint32  AS_GetData	(const AS5040* );

#endif