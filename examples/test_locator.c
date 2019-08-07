/**
This program places the keyboard in RAW EVENT mode.

You use the keyboard to control the locator's mode:
    i -- inactive
    s -- sample
    e -- event

You also use the keyboard to control the echo attribute:
    c -- cursor
    l -- rubber line
    r -- rubber rect

You can control button mask in this way:
    1 -- toggles the status of the LEFT button in the button mask
             ... etc. ...   for 2 (MIDDLE) and 3 (RIGHT)

You quit by typing:
    q -- QUIT
**/


#include "srgp.h"
#include <stdlib.h>


static deluxe_locator_measure dlm;
static char buffer[100];
static char kmstring[2];
static deluxe_keyboard_measure dkm;

static int lineheight, textw, texta, textd;

static int timeout;

static int locatorMode = INACTIVE;
static char *modeNames[] = {"INACTIVE", "SAMPLE", "EVENT"};

static int locatorButtonMask = LEFT_BUTTON_MASK;


static void DisplayLocatorMeasure ()
{
   int y = 400;

   SRGP_setColor (COLOR_WHITE);
   SRGP_fillRectangleCoord (0, (400-(7*lineheight)-textd), 1000, 400);
   
   SRGP_setColor (COLOR_BLACK);

   y -= lineheight;
   sprintf (buffer, "LOCATOR MODE: %s", modeNames[locatorMode]);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   if (locatorMode == INACTIVE) {
      y -= 2*lineheight;
      SRGP_text (SRGP_defPoint(10,y), 
		 "For instructions on how to use this demo,");
      y -= lineheight;
      SRGP_text (SRGP_defPoint(10,y), 
		 "    you must consult the demo README file,");
      y -= lineheight;
      SRGP_text (SRGP_defPoint(10,y), 
		 "    or the comment in the source file itself.");
      y -= lineheight;
      SRGP_text (SRGP_defPoint(10,y), 
		 "Use 'q' to quit, and then read the instructions.");
      return;
   }

   y -= lineheight;
   sprintf (buffer, "Button mask: %s  %s  %s", 
	    (locatorButtonMask&LEFT_BUTTON_MASK) == 0 ? "----" : "LEFT",
	    (locatorButtonMask&MIDDLE_BUTTON_MASK) == 0 ? "------" : "MIDDLE",
	    (locatorButtonMask&RIGHT_BUTTON_MASK) == 0 ? "-----" : "RIGHT");
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Position: %3d, %3d", dlm.position.x, dlm.position.y);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Button chord: %d, %d, %d", 
	    dlm.button_chord[0], dlm.button_chord[1], dlm.button_chord[2]);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Button of last transition: %d", 
	    dlm.button_of_last_transition);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Modifier chord: %d, %d, %d", 
	    dlm.modifier_chord[0], dlm.modifier_chord[1], 
	    dlm.modifier_chord[2]);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Timestamp: %8d seconds, %2d ticks", 
	    dlm.timestamp.seconds, dlm.timestamp.ticks);
   SRGP_text (SRGP_defPoint(10,y), buffer);
}





main()
{
   SRGP_begin ("Locator exercise", 600, 400, 1, FALSE);


   SRGP_setInputMode (KEYBOARD, EVENT);
   SRGP_setKeyboardProcessingMode (RAW);

   dkm.buffer = kmstring;
   dkm.buffer_length = 2;

   SRGP_inquireTextExtent ("High", &textw, &texta, &textd);
   lineheight = texta + textd;

   SRGP_setInputMode (LOCATOR, INACTIVE);
   DisplayLocatorMeasure();

   while (1) {
      timeout = (locatorMode == SAMPLE) ? 20 : -1;
      switch (SRGP_waitEvent (timeout)) {
       case NO_DEVICE:
	 SRGP_sampleDeluxeLocator (&dlm);
	 DisplayLocatorMeasure();
	 break;
       case LOCATOR:
	 SRGP_getDeluxeLocator (&dlm);
	 DisplayLocatorMeasure();
	 break;
       case KEYBOARD:
	 SRGP_getDeluxeKeyboard (&dkm);
	 switch (dkm.buffer[0]) {
	  case '1':
	    locatorButtonMask ^= LEFT_BUTTON_MASK;
	    SRGP_setLocatorButtonMask (locatorButtonMask);
	    DisplayLocatorMeasure();
	    break;
	  case '2':
	    locatorButtonMask ^= MIDDLE_BUTTON_MASK;
	    SRGP_setLocatorButtonMask (locatorButtonMask);
	    DisplayLocatorMeasure();
	    break;
	  case '3':
	    locatorButtonMask ^= RIGHT_BUTTON_MASK;
	    SRGP_setLocatorButtonMask (locatorButtonMask);
	    DisplayLocatorMeasure();
	    break;
	  case 'i': 
	    SRGP_setInputMode (LOCATOR, INACTIVE); 
	    locatorMode = INACTIVE;
	    DisplayLocatorMeasure();
	    break;
	  case 's': 
	    SRGP_setInputMode (LOCATOR, SAMPLE); 
	    locatorMode = SAMPLE;
	    DisplayLocatorMeasure();
	    break;
	  case 'e': 
	    SRGP_setInputMode (LOCATOR, EVENT);
	    locatorMode = EVENT;
	    DisplayLocatorMeasure();
	    break;
	  case 'c': 
	    SRGP_setLocatorEchoType (CURSOR);
	    break;
	  case 'l': 
	    SRGP_setLocatorEchoType (RUBBER_LINE);
	    break;
	  case 'r': 
	    SRGP_setLocatorEchoType (RUBBER_RECT);
	    break;
	  case 'q': 
	    SRGP_end();
	    exit(0);
	 }
      }
   }
}
