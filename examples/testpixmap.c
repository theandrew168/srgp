#include "srgp.h"
#include <stdio.h>

main()
{
   FILE *f;

   SRGP_begin ("Testing pixmap patterns", 800,800,7,FALSE);
   SRGP_enableSynchronous ();

   SRGP_loadCommonColor (0, "black");
   SRGP_loadCommonColor (1, "blue");
   SRGP_loadCommonColor (2, "green");
   SRGP_loadCommonColor (3, "cyan");
   SRGP_loadCommonColor (4, "red");
   SRGP_loadCommonColor (5, "magenta");
   SRGP_loadCommonColor (6, "yellow");
   SRGP_loadCommonColor (7, "white");

   SRGP_setInputMode (LOCATOR, EVENT);

   f = fopen ("pixpatdefs", "r");
   if (SRGP_loadPixmapPatternsFromFile (f)) {
      fprintf (stderr, "SOMETHING BAD HAPPENED.\n"); 
      exit(1);
   }
   fclose(f);

   SRGP_setFillPixmapPattern (0);
   SRGP_setFillStyle (PIXMAP_PATTERN);
   SRGP_fillEllipse (SRGP_defRectangle(5,5, 500,200));
   SRGP_waitEvent (INDEFINITE);

   f = fopen ("bitpatdefs", "r");
   if (SRGP_loadBitmapPatternsFromFile (f)) {
      fprintf (stderr, "SOMETHING BAD HAPPENED.\n"); 
      exit(1);
   }
   fclose(f);
   SRGP_setFillBitmapPattern (106);
   SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE);
   SRGP_fillEllipse (SRGP_defRectangle(5,5, 500,200));
   SRGP_waitEvent (INDEFINITE);

   SRGP_setColor (4);
   SRGP_setFillBitmapPattern (0);
   SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE);
   SRGP_fillEllipse (SRGP_defRectangle(5,5, 500,200));
   SRGP_waitEvent (INDEFINITE);
}
