/*===============================================
                 hfloats.h

  Header file for hardware floats routines.
===============================================*/

/* ----------------------------------------*/
/*            Include                      */
/* ----------------------------------------*/
#include <math.h>
#include <sys/ucontext.h>
#include <fpu_control.h>

/* ----------------------------------------*/
/*            Hardware Floats              */
/* ----------------------------------------*/

/* DECstations: */
typedef struct {
  unsigned mant_l  : 32;
  unsigned mant_h  : 20;
  unsigned exp     : 11;
  unsigned sign    : 1;
  } ieee_rep;

/* SPARCstations: 
typedef struct {
  unsigned sign    : 1;
  unsigned exp     : 11;
  unsigned mant_h  : 20;
  unsigned mant_l  : 32;
  } ieee_rep; */

typedef union {
  double num;
  ieee_rep rep;
  }  ieee;

#define BIAS 1023
#define MAXEXP 1023
#define MAXEXP1 1024
#define MINEXP -1022
#define MINEXP1 -1023
#define PREC 53
#define PREC1 52

/* ----------------------------------------*/
/*            Rounding modes               */
/* ----------------------------------------*/

/* DECstations:                                        */
/* #define rounddown() swapRM(ROUND_TO_MINUS_INFINITY) */
/* #define roundup()   swapRM(ROUND_TO_PLUS_INFINITY)  */

/* Sun SPARCs: see also man ieee_flags and /usr/include/ieeefp.h */
/*  #define rounddown() fpsetround(FP_RM) */
/*  #define roundup() fpsetround(FP_RP) */

/* Linux */
#define rounddown() { fpu_control_t cw; _FPU_GETCW(cw); cw= (cw & ~0x0C00)|_FPU_RC_DOWN; _FPU_SETCW(cw); }
#define roundup() { fpu_control_t cw; _FPU_GETCW(cw); cw= (cw & ~0x0C00)|_FPU_RC_UP; _FPU_SETCW(cw); }

/* ----------------------------------------*/
/*            Hardware intervals           */
/* ----------------------------------------*/

typedef struct {
  double left, right;
} interval;

static interval izero = { 0.0, 0.0 };
static interval ione  = { 1.0, 1.0 };

