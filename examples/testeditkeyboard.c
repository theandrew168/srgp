#include "srgp.h"
#include <stdio.h>
#ifdef THINK_C
#include <unix.h>
#endif



/* TEST OF KEYBOARD DEVICE */
main(argc,argv)
int argc;
char **argv;
{
   char km[81];
   int trunccount;


   SRGP_begin (argv[0], 700,700, 3, FALSE);
   SRGP_enableBlockedWait();

   SRGP_loadCommonColor (5, "maroon");
   SRGP_setKeyboardEchoColor (5);

   SRGP_loadCommonColor (6, "navy");
   SRGP_setColor (6);

   SRGP_setKeyboardEchoOrigin (SRGP_defPoint(100,600));
   SRGP_text (SRGP_defPoint(5,650), 
	      "How many chars to truncate to?  (<80 please)");

   SRGP_setInputMode (KEYBOARD, EVENT);
   SRGP_waitEvent(-1);
   SRGP_getKeyboard (km, 81);
   sscanf (km, "%d", &trunccount);

   SRGP_setKeyboardEchoOrigin (SRGP_defPoint(100,450));
   SRGP_text (SRGP_defPoint(5,500), "Enter string to be truncated:");

   SRGP_waitEvent(-1);
   SRGP_getKeyboard (km, trunccount+1);
   SRGP_setInputMode (KEYBOARD, INACTIVE);

   SRGP_text (SRGP_defPoint(5,200), "I'm printing to stdout...");
   fprintf (stderr, "Here's the truncated string: %s\n", km);

   SRGP_text (SRGP_defPoint(5,100), "Goodbye!");
   sleep(3);


}
