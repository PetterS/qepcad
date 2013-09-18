#ifndef _TRUTHBYTOP_HEADER_
#define _TRUTHBYTOP_HEADER_

#include "adj2D.h"

void GADDVERTEX(Word v, Word l, Word *G_);
Word GSTACKHANDLE(Word i, Word G_);
Word GVERTEXHANDLE(Word v, Word G_);
Word GVERTEXLABEL(Word v, Word G_);
void GNEWLABEL(Word v, Word l, Word G_);
void GADDEDGE(Word e, Word G_);
Word GSUCCLIST(Word v, Word G_);
Word vert2dim(Word v);
Word GPREDLIST(Word v, Word G_);

#endif
