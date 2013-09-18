/*===============================================
               sactypes.h

  Header file for SACLIB type definitions
===============================================*/
#ifndef SACTYPES_H
#define SACTYPES_H

#include "sacsys.h"

typedef struct {Word next; Word flag; Word len; Word *array;} GCArray;

#define BDigit  Word

#define DWord long long

#endif
