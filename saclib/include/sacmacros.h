/*===========================================================================
			  sacmacros.h

Header file for SACLIB macro definitions
===========================================================================*/
#ifndef SACMACROS_H
#define SACMACROS_H

#include "sacsys.h"
#include "sactypes.h"

/*---------------------------------------------------------------------------
		The canonical saclib version number.
---------------------------------------------------------------------------*/
#define SACMAJVERS 2
#define SACMINVERS 2
#define SACREVVERS 4

/*---------------------------------------------------------------------------
		Macros that are always defined.
---------------------------------------------------------------------------*/
#ifdef NO_SACLIB_MACROS
#define FIRST(L)       SPACEB1[(L)]
#define GCAGET(A,i)    (GCASPACEBp[(A)].array[(i)])
#define GCASET(A,i,a)  (GCASPACEBp[(A)].array[(i)] = (a))
#define ISNIL(a)       ((a) == NIL)
#define ISZERO(a)      ((a) == 0)
#define RED(L)         SPACEB[(L)]
#define SFIRST(L,a)    (SPACEB1[(L)] = (a))
#define SRED(L,Lp)     (SPACEB[(L)] = (Lp))
#endif
#define ILENGTH(A)     (((A) < BETA) ? 1 : LENGTH(A))
#define ILOG2A(A,n)    (((n)==0) ? 0 : ((n)-1)*ZETA + DLOG2((A)[(n)-1]))
#define ISIGNA(A,n)    ((n) == 0 ? 0 : (((A)[(n)-1] > 0) ? 1 : -1))

#define absm(a)        (((a) >= 0) ? (a) : -(a))
#define maxm(a,b)      (((a) > (b)) ? (a) : (b))
#define minm(a,b)      (((a) < (b)) ? (a) : (b))
#define signm(a)       ((a) > 0 ? 1 : ((a) < 0 ? -1 : 0))

/*---------------------------------------------------------------------------
			     Arrays.
---------------------------------------------------------------------------*/

#define FREEARRAY(A)   free((A))


/*---------------------------------------------------------------------------
		       Array polynomials.
---------------------------------------------------------------------------*/

/* MAP coefficient */
#define MAPCF(A,e)  (A[e])

/* MAP degree */
#define MAPDEG(A)   (A[-1])

/* MAP free memory */
#define MAPFREE(A)  FREEARRAY((A)-1)

/* MAP get memory */
#define MAPGET(n)   (GETARRAY((n)+2) + 1)

/* MAP leading coefficient */
#define MAPLDCF(A)  (MAPCF(A,MAPDEG(A)))

/* MAP zero test */
#define MAPZERO(A)  (MAPDEG(A) == 0 && MAPCF(A,0) == 0)


/*---------------------------------------------------------------------------
		 Finite ring array polynomials.
---------------------------------------------------------------------------*/

/* FRAP degree */
#define FRAPDEG(A) (A[-1][0])

/* FRAP size---the size of the array */
#define FRAPSIZE(A) (A[-1][1])

/* FRAP coefficient */
#define FRAPCF(A,i)  (A[i])

/* FRAP leading coefficient */
#define FRAPLDCF(A)  (FRAPCF(A,FRAPDEG(A)))

/* FRAP zero test */
#define FRAPZERO(A) (FRAPDEG(A) == 0 && MAPZERO(FRAPLDCF(A)))


/*---------------------------------------------------------------------------
			   Matrices.
---------------------------------------------------------------------------*/

/* matrix element */
#define MATELT(M,i,j)  (M[i][j])

#ifndef NO_SACLIB_MACROS


/*---------------------------------------------------------------------------
			List processing.
---------------------------------------------------------------------------*/

#define RED2(L)        RED(RED(L))
#define SECOND(L)      FIRST(RED(L))


/* Arithmetic */

#define ODD(a)         ((a) & 1)
#define EVEN(a)        (!ODD(a))
#define DAND(a,b)      ((a) & (b))
#define DOR(a,b)       ((a) | (b))
#define DNOT(a)        (~(a))
#define DNIMP(a,b)     ((a) & ~(b))
#define MDSUM(m,a,b)  (((a)+(b))%(m))


/***
 *
 * The following macros give troubles w.r.t. side effects and therefore
 * are commented out for the time being.
 *
 ***/

/*
#define ISATOM(a)      (-BETA < (a) && (a) < BETA)
#define ISLIST(a)      ((BETA < (a) && (a) < BETAp && ((a) & 1)) || (a) == BETA)
#define ISOBJECT(a)    (ISATOM(a) || ISLIST(a))
#define ISGCA(a)       (BETAp < (a) && (a) < BETApp)
#define ADV(L,a,Lp)    do {*(a)=FIRST(L); *(Lp)=RED(L);} while (0)
#define QREM(a,b,q,r)  do {*(q)=(a)/(b); *(r)=(a)%(b);} while (0)
#define MDDIF(m,a,b)   (((a)-(b)+(m))%(m))
#define MDNEG(m,a)     ((a)==0?0:(m)-(a))
*/

#endif /* NO_SACLIB_MACROS */

#endif /* SACMACROS_H */
