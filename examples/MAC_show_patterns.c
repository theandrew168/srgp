#include "srgp.h"
#ifdef THINK_C
#include <unix.h>
#endif

#define chipwidth 20
#define chipheight 20
#define vertmarg 5
#define horizmarg 27

#define heightofcanvas0  400

int i, x, y;
int whichdev;
char str[10];   

attribute_group bund;

unsigned short redi, greeni, bluei;


static void ShowPat (int num, char *numstr)
{
   SRGP_setFillBitmapPattern (num);
   SRGP_fillRectangleCoord (x, y, x + chipwidth, y + chipheight);
   SRGP_text (SRGP_defPoint(x + chipwidth+4, y+8), numstr);
   y = y + chipheight+vertmarg;
}

main()
{
   SRGP_begin ("SRGP Patterns", 600,heightofcanvas0, 2, FALSE);
   SRGP_text (SRGP_defPoint(5, heightofcanvas0-15),
	      "Drawn in black in REPLACE mode.  Color use demonstrated on far right.");

   x = 5;
   y = 5;

#ifdef THINK_C
   SRGP_loadFont (0, "Monaco.9");
#endif

   SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE);

   for (i=0; i<=104; i++) {
      sprintf (str, "%2d", i);
      ShowPat(i, str);
      if (y > (heightofcanvas0-40)) {
	 y = 5;
	 x = x + chipwidth + horizmarg;
      }
   }

   SRGP_loadCommonColor (2, "red");
   SRGP_loadCommonColor (3, "green");
   
   SRGP_setColor (2);
   SRGP_setBackgroundColor (3);

   y = 5;
   x = x + chipwidth + horizmarg;

   for (i=0; i<=35; i++) {
      sprintf (str, "%2d", i);
      ShowPat(i, str);
      if (y > (heightofcanvas0-40)) {
	 y = 5;
	 x = x + chipwidth + horizmarg;
      }
   }
   SRGP_waitEvent (INDEFINITE);
}
