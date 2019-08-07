#include "srgp.h"

#define chipwidth 40
#define chipheight 40
#define vertmarg 10
#define horizmarg 40

int i, x, y;
int whichdev;
char str[10];   

ShowPat (num, numstr)
int num;
char *numstr;
{
   SRGP_setFillBitmapPattern (num);
   SRGP_fillRectangleCoord (x, y, x + chipwidth, y + chipheight);
   SRGP_text (SRGP_defPoint(x + chipwidth+4, y+8), numstr);
   y = y + chipheight+vertmarg;
}

main()
{
   SRGP_begin ("SRGP Patterns", 950,720, 2, FALSE);
   SRGP_text (SRGP_defPoint(5, 700),
	      "SRGP patterns (drawn in black in REPLACE mode)");
   SRGP_text (SRGP_defPoint(5, 680),
	      "On far right, use of color is shown.");
   SRGP_text (SRGP_defPoint(45, 660), "Hit any key to exit...");

   x = 5;
   y = 5;


   SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE);

   for (i=0; i<=104; i++) {
      sprintf (str, "%2d", i);
      ShowPat(i, str);
      if (y > 600) {
	 y = 5;
	 x = x + chipwidth + horizmarg;
      }
   }

   SRGP_loadCommonColor (2, "red");
   SRGP_loadCommonColor (3, "blue");
   SRGP_setColor (2);
   SRGP_setBackgroundColor (3);

   y = 5;
   x = x + chipwidth + horizmarg;

   for (i=0; i<=35; i++) {
      sprintf (str, "%2d", i);
      ShowPat(i, str);
      if (y > 600) {
	 y = 5;
	 x = x + chipwidth + horizmarg;
      }
   }
   SRGP_setKeyboardProcessingMode (RAW);
   SRGP_setInputMode (KEYBOARD, EVENT);
   whichdev = SRGP_waitEvent(-1);
}
