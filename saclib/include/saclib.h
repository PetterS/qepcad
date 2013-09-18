/*===========================================================================
				  saclib.h

Header file for SACLIB
===========================================================================*/
#ifndef SACLIB_H
#define SACLIB_H

#include "sacsys.h"
#include "sactypes.h"
#include "hfloats.h"
#include <stdlib.h>


/*-------------------------------------------
  Constants
-------------------------------------------*/

#define NIL            BETA

#define GC_CHECK    0
#define GC_NO_CHECK 1

#define SAC_KEEPMEM 0
#define SAC_FREEMEM 1

/* FIXED   = dimension of fixed size array used in IPROD  to hold
 * the operands. FIXEDX2 / 2 > FIXED >= MAXCLASSICAL.
 */
#define FIXED    200

/* FIXEDX2 =  dimension of fixed size array used in IPROD to hold
 * the result. FIXEDX2 > FIXED * 2.
 */
#define FIXEDX2  401

/* WORK is the dimension of the fixed size work array for KARATSUBA
 * it has to be >= 2(FIXED - a + 3 floor(log_2(FIXED - 3))),
 * where a = 2^(k - 1) + 3 * k
 * and k = ceiling(log_2(MAXCLASSICAL - 3)).
 */
#define WORK     400

/* If integers are of length  <= MAXCLASSICAL
 * classical multiplication is used,
 * i.e. the Karatsuba algorithm is not invoked.
 * MAXCLASSICAL <= FIXED.
 * Also the Karatsuba algorithm KARATSUBA uses classical multiplication
 * for operands of length <= MAXCLASSICAL.
 * The Karatsuba algorithm requires MAXCLASSICAL >= 4.
 */
#define MAXCLASSICAL  14


/*-------------------------------------------
  Function Prototypes
-------------------------------------------*/

#include "sacproto.h"


/*-------------------------------------------
  Macros
--------------------------------------------*/

#include "sacmacros.h"


/*-------------------------------------------
  External Variables
-------------------------------------------*/

/* List processing
 */
extern Word AVAIL;
extern char *BACSTACK;
extern Word GCC;
extern Word GCCC;
extern Word GCAC;
extern Word GCGLOBALS;
extern Word GCM;
extern Word NU;
extern Word RHO;
extern Word *SPACE;
extern Word *SPACEB;
extern Word *SPACEB1;
extern Word GCAAVAIL;
extern GCArray *GCASPACE;
extern GCArray *GCASPACEBp;
extern Word NUp;
extern Word BETAp;
extern Word BETApp;

/* Timing
 */
extern Word TAU;
extern Word TAU0;
extern Word TAU1;

/* Integer arithmetic
 */
extern Word DELTA;
extern Word EPSIL;
extern Word ETA;
extern Word RINC;
extern Word RMULT;
extern Word RTERM;
extern Word TABP2[];
extern Word THETA;
extern Word TMI[128];
extern Word ZETA;

/* Miscellaneous
 */
extern BDigit *FFPLUS1;
extern BDigit FFSIZE;
extern Word NPFDS;
extern Word SPRIME;
extern Word NSPRIME;
extern Word MPRIME;
extern Word NMPRIME;
extern Word LPRIME;
extern Word NLPRIME;
extern Word UZ210;
extern Word NPTR1;
extern Word GCAPTR1;

/* Input/Output
 */
extern Word LASTCHAR;

#endif
