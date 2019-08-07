#include "srgp.h"
#include <stdio.h>
#include <stdlib.h>

main()
{
   deluxe_locator_measure locmeasure;
   int whichdev;
   char buff[50];


   SRGP_begin ("Testing timestamps!", 400,400, 1, FALSE);

   SRGP_setLocatorButtonMask(LEFT_BUTTON_MASK);
   SRGP_setInputMode(LOCATOR, EVENT);   

   while (1) {
      SRGP_waitEvent(INDEFINITE);
      SRGP_getDeluxeLocator(&locmeasure);
      if (locmeasure.modifier_chord[SHIFT] == DOWN)
	 exit(0);
      sprintf (buff, "%d:%2d", 
	       locmeasure.timestamp.seconds, locmeasure.timestamp.ticks);
      SRGP_text (locmeasure.position, buff);
      /* Swallow the UP event. */
      while(LOCATOR!=SRGP_waitEvent(INDEFINITE));
   }
}

