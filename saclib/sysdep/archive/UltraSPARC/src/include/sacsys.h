/******************************************************************\
  FILE
    sacsys.h
 
  Header file containing system dependent definitions.
\******************************************************************/

#ifndef SACSYS_H
#define SACSYS_H

/* SACLIB 'Word' is a C 'int'. */
typedef int     Word;

/* Words are 32 bits. */
#define BETA    0x20000000 
#define BETA1   0x1fffffff   /* BETA - 1 */

/* Default values of several global variables. */
#define NU_       1000000  /* 4 MB list space - 500000 list cells. */
#define NUp_      1000
#define NPRIME_   1000
#define NPFDS_    5
#define NSMPRM_   500
#define RHO_      10
#define NPTR1_    2001

/* Does the compiler support function prototypes? */
#ifdef __STDC__
#define P__(A)  A
#else
#define P__(A)  ()
#endif

#endif
