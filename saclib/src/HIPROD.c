/*======================================================================
                        K <- HIPROD(I,J)

Hardware interval product.  

Inputs
   I, J : hardware intervals.

Output
   K : the smallest hardware interval containing I * J.

Warning
   HIPROD is not floating-point overflow-underflow protected.
======================================================================*/
#include "saclib.h"

interval HIPROD(I,J)

       interval I,J;
{
       double a1,a2,b,b1,b2,c1,c2,d1,d2;
       interval K;

Step1: /* Extract endpoints. */
	a1 = I.left;
	a2 = I.right;
	b1 = J.left;
	b2 = J.right;

Step2: /* a1 >= 0. */
	if (a1 >= 0) {
	   if (b1 >= 0) {
              rounddown();
              K.left = a1 * b1;
              roundup();
              K.right = a2 * b2; }
	   else if (b2 < 0) {
              rounddown();
              K.left = a2 * b1;
              roundup();
              K.right = a1 * b2; }
           else {
              rounddown();
              K.left = a2 * b1;
              roundup();
              K.right = a2 * b2; }
	   goto Return; }

Step3: /* a2 < 0. */
	if (a2 < 0) {
           if (b1 >= 0) {
              rounddown();
              K.left = a1 * b2;
              roundup();
              K.right = a2 * b1; }
           else if (b2 < 0) {
              rounddown();
              K.left = a2 * b2;
              roundup();
              K.right = a1 * b1; }
           else {
              rounddown();
              K.left = a1 * b2;
              roundup();
              K.right = a1 * b1; }
	   goto Return; }

Step4: /* a1 < 0 <= a2. */
	if (b1 >= 0) {
           rounddown();
           K.left = a1 * b2;
           roundup();
           K.right = a2 * b2; }
        else
           if (b2 < 0) {
              rounddown();
              K.left = a2 * b1;
              roundup();
              K.right = a1 * b1; }
        else {
           rounddown();
           c1 = a1 * b2;  
           c2 = a2 * b1;
           roundup();
           d1 = a1 * b1;  
           d2 = a2 * b2;
           if (c1 < c2) 
              K.left = c1; 
           else 
              K.left = c2;
           if (d1 > d2) 
              K.right = d1; 
           else 
              K.right = d2; }

Return: /* Return K. */
	return K;
}
