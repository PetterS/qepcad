/************************************************************
FUNCTIONS FOR CONSTRUCTING UNNORMALIZED FORMULAS FOR INPUT
TO QEPCADB.

    Example:  Suppose P and Q are 3-variate saclib polynomials.

    Word QFF = UNFIMPLIES(UNATF(EQOP,P,3),UNATF(GTOP,P,3);
    Word   F = UNQIF(3,QB(UNIVER,3),QFF);

    Produces an unnormalized input formula for the decision
    problem "for all x,y,z [ P(x,y,z) = 0 ==> Q(x,y,z) > 0 ]".

The following constants are needed to create formulas.  They
are actually defined in "qepcad.h".

Strict Relational Operators: LTOP,EQOP,GTOP   
Other Relational Operators : GEOP,NEOP,LEOP   

Quantifiers:
 UNIVER    for all
 EXIST     there exists
 CONTQ     for exactly a continuous set
 FULLDE    there exist infinitely many
 FULLDA    for all but finitely many
 EXISTk    there exist exactly k
*************************************************************/

/************************************************************
 UnNormalized Atomic Tarski Formula
 Input:  op a relational operator (constant from above list)
         P an r-variate saclib polynomial
         r the number of variables in P
 Output: F an unnormalized atomic formula representing "P op 0".
*************************************************************/
inline Word UNATF(Word op, Word P, BDigit r)
{
  return LIST4(op,P,r,NIL);
}

/************************************************************
 UnNormalized Atomic Extended Tarski Formula
 Input:  op a relational operator (constant from above list)
         P an r-variate saclib polynomial s.t. deg_{xr}(P) > 0
         r the number of variables in P
         j an index for a root, i.e. nonzero BDigit
 Output: F an unnormalized atomic formula representing 
         "_root_j P op 0"
*************************************************************/
inline Word UNAETF(Word op, Word P, BDigit r, Word j)
{
  return LIST6(IROOT,op,j,P,r,NIL);
}

/************************************************************
Functions for combining quantifier-free formulas
*************************************************************/
// Unnormalized formula AND
inline Word UNFAND(Word F1, Word F2) { return LIST3(ANDOP,F1,F2); }

// Unnormalized formula OR
inline Word UNFOR(Word F1, Word F2){ return LIST3(OROP,F1,F2); }

// Unnormalized formula IMPLIES
inline Word UNFIMPLIES(Word F1, Word F2) { return LIST3(RIGHTOP,F1,F2); }

// Unnormalized formula EQUIVALENT
inline Word UNFEQUIV(Word F1, Word F2) { return LIST3(EQUIOP,F1,F2); }

// Unnormalized formula NOT
inline Word UNFNOT(Word F) { return LIST2(NOTOP,F); }


/************************************************************
Functions for producing Unnormalized quantified input formulas.
*************************************************************/
// Unnormalized quantified input formula
// n, number of variables, QL the quantifier list, QFF the 
// quantifier-free part of the input formula.
inline Word UNQIF(Word n, Word QL, Word QFF)
{
  return LIST4(n,n-LENGTH(QL),QL,QFF);
}

// Quantifier block
// Q: the quantifier, t the number of variables in the block
// Quantifiers come from the constants above or, in the case
// of EXISTk a quantifer is "LIST2(EXISTk,k)" where k is the
// the number of solutions specified.
// NOTE: Use saclib's CONC function to concatenate quantifer
// blocks into a single quantifier list.
inline Word QB(Word Q, Word t)
{
  Word L = NIL; 
  for(int i = 0; i < t; ++i) L = COMP(Q,L);
  return L;
}
