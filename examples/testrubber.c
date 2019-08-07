#include "srgp.h"
#include <stdio.h>

/* TEST OF LOCATOR DEVICE RUBBER LINE ECHO MODE */

/* Also tests the keyboard in raw mode. */

/* A left button press adds the new point to the polyline.
   A right button press sets a new anchor point.
   A middle button press is never seen (masked out).
   Hitting 'Q' at any time should cause the application to exit.
   */

main()
{
   locator_measure locmeasure, pastlocmeasure;
   char keymeasure[81];
   int whichdev;


   SRGP_begin ("Test of rubber echo", 400,400,1,FALSE);

   SRGP_setLocatorEchoType(CURSOR);
   SRGP_setLocatorButtonMask(LEFT_BUTTON_MASK | RIGHT_BUTTON_MASK);
   pastlocmeasure.position = SRGP_defPoint(5,5);
   SRGP_setLocatorMeasure(pastlocmeasure.position);
   SRGP_setKeyboardProcessingMode (RAW);
   SRGP_setInputMode(LOCATOR, EVENT);   
   SRGP_setInputMode(KEYBOARD, EVENT);
   SRGP_setLocatorEchoRubberAnchor(pastlocmeasure.position);
   SRGP_setLocatorEchoType (RUBBER_LINE);
   SRGP_setLineStyle(DASHED);

   while (1) {
      whichdev = SRGP_waitEvent(INDEFINITE);
      if (whichdev == KEYBOARD) {
        SRGP_getKeyboard(keymeasure,80);
        if (keymeasure[0] == 'Q') break;
      }
      else {
         SRGP_getLocator(&locmeasure);
         SRGP_setLocatorEchoRubberAnchor(locmeasure.position);
	 if (locmeasure.button_of_last_transition == LEFT_BUTTON)
	    SRGP_line(pastlocmeasure.position, locmeasure.position);
	 SRGP_beep();
         pastlocmeasure = locmeasure;
	 /* Swallow the UP event. */
         while(LOCATOR!=SRGP_waitEvent(INDEFINITE));
      }
   }
}
