#include "srgp.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned short *redd, *greenn, *bluee;
static int width=400, height=400;
static int ncolors;

void Draw(void);
int DealWithResizeEvent (int w,int h);

void Draw()
{
   register i;

   SRGP_setPlaneMask (ncolors-1);

   SRGP_setLineWidth (1);
   for (i=0; i<height; i++) {
/*      SRGP_setColor (i & (ncolors-1));*/
      SRGP_setColor ((((double)ncolors / (double)height)) * i);
      SRGP_lineCoord (0,i, width,i);
   }

   i = (3<<5) | 7;
   SRGP_setPlaneMask (i);
   SRGP_setLineWidth (2);
   SRGP_setColor (0);
   SRGP_lineCoord (width>>1, 0, width>>1, height);
   SRGP_lineCoord (0, height>>1, width, height>>1);
}


int DealWithResizeEvent (w,h)
{
   width = w;
   height = h;
   SRGP_setClipRectangle (SRGP_defRectangle(0,0,w-1,h-1));
   Draw();
}


main()
{
   register i;
   unsigned short maxpixval = (unsigned short) -1;


   SRGP_beginWithDebug ("Test of resizing", width, height, 8, FALSE);
   SRGP_enableBlockedWait();
   SRGP_allowResize (TRUE);
   SRGP_registerResizeCallback (DealWithResizeEvent);

   ncolors = 1 << SRGP_inquireCanvasDepth();
   redd = (unsigned short *) malloc (ncolors * sizeof(unsigned short));
   greenn = (unsigned short *) malloc (ncolors * sizeof(unsigned short));
   bluee = (unsigned short *) malloc (ncolors * sizeof(unsigned short));
   
   for (i=0; i < ncolors; i++) {
      redd[i] = maxpixval * ((double)i/(double)ncolors);
      greenn[i] = ((double)maxpixval/2.0) * ((double)i/(double)ncolors);
      bluee[i] = maxpixval - redd[i];
   }
   SRGP_loadColorTable (0, ncolors, redd+2, greenn+2, bluee+2);

   Draw();

   SRGP_setInputMode (LOCATOR, EVENT);
   while (1) {
      SRGP_waitEvent(-1);
      SRGP_changeScreenCanvasSize (100,100);
   }
}
