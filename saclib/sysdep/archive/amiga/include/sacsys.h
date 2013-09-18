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
#define BETA    ((int)0x20000000)
#define BETA1   ((int)0x1fffffff)   /* BETA - 1 */

/* Default values of several global variables. */
#define NU_       ((int)50000)      /* 200 K list space - 25000 list cells. */
#define NUp_      ((int)100)
#define NPRIME_   ((int)500)
#define NPFDS_    ((int)5)
#define NSMPRM_   ((int)500)
#define RHO_      ((int)10)
#define NPTR1_    ((int)2001)

/* Does the compiler support function prototypes? */
#ifdef __STDC__
#define P__(A)  A
#else
#define P__(A)  ()
#endif

#endif
