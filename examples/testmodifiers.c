#include "srgp.h"
#include <malloc.h>
#include <stdio.h>

/* Only the left button is ever seen. */
/* Any unmodified button press adds the new point to the polyline.
   A SHIFT-modified button press sets a new anchor point.
   A META-modified button press causes the application to exit.
      (WARNING: your window manager MAY be swallowing all meta'ed events!)
   A META-modified 'Z' also causes the application to exit.
   */

main()
{
   deluxe_locator_measure locmeasure, pastlocmeasure;
   deluxe_keyboard_measure keymeasure;
   int whichdev;

   keymeasure.buffer = malloc(51);
   keymeasure.buffer_length = 50;

   SRGP_begin ("Test of modifiers", 800,800,1,FALSE);

   SRGP_setLocatorEchoType(CURSOR);
   SRGP_setLocatorButtonMask(LEFT_BUTTON_MASK);
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
      switch (whichdev) {
      case LOCATOR:
	 SRGP_getDeluxeLocator(&locmeasure);
	 if (locmeasure.button_chord[LEFT_BUTTON] == UP)
	    break;
	 if (locmeasure.modifier_chord[META] == DOWN)
	    exit(0);
	 SRGP_setLocatorEchoRubberAnchor(locmeasure.position);
	 if (locmeasure.modifier_chord[SHIFT] == UP)
	    SRGP_line(pastlocmeasure.position, locmeasure.position);
	 else
	    SRGP_beep();
	 pastlocmeasure = locmeasure;
	 break;
      case KEYBOARD:
	 SRGP_getDeluxeKeyboard(&keymeasure);
	 if ((keymeasure.modifier_chord[META] == DOWN) && 
	     (keymeasure.buffer[0] == 'Z'))
		 exit(0);
	 break;
      }
   }
}
