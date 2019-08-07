/**
This program places the keyboard in RAW EVENT mode.
**/


#include "srgp.h"
#include <stdlib.h>


static deluxe_locator_measure dlm;
static char buffer[100];
static char kmstring[2];
static deluxe_keyboard_measure dkm;

static int lineheight, textw, texta, textd;

static int timeout;

static int locatorMode = SAMPLE;
static char *modeNames[] = {"INACTIVE", "SAMPLE", "EVENT"};

static int locatorButtonMask = LEFT_BUTTON_MASK;


static void DisplayPrompt (void)
{
   int y = 100;
   
   y -= lineheight;
   SRGP_text (SRGP_defPoint(10,y), "Hit any keyboard key ('q' to exit)");
}   

static void DisplayKeyboardMeasure (void)
{
   int y = 100;

   SRGP_setColor (COLOR_WHITE);
   SRGP_fillRectangleCoord (0,0, 400, 400);
   
   SRGP_setColor (COLOR_BLACK);
   
   y -= lineheight;
   sprintf (buffer, "Value: %c (hex %4x)", dkm.buffer[0], dkm.buffer[0]);
   SRGP_text (SRGP_defPoint(10,y), buffer);
   
   y -= lineheight;
   sprintf (buffer, "Modifier chord: %d, %d, %d", 
	    dkm.modifier_chord[0], dkm.modifier_chord[1], 
	    dkm.modifier_chord[2]);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Timestamp: %8d seconds, %2d ticks", 
	    dkm.timestamp.seconds, dkm.timestamp.ticks);
   SRGP_text (SRGP_defPoint(10,y), buffer);
}





main()
{
   SRGP_begin ("Keyboard exercise", 400, 100, 1, FALSE);

   SRGP_setInputMode (KEYBOARD, EVENT);
   SRGP_setKeyboardProcessingMode (RAW);

   dkm.buffer = kmstring;
   dkm.buffer_length = 2;

   SRGP_inquireTextExtent ("High", &textw, &texta, &textd);
   lineheight = texta + textd;
   
   DisplayPrompt();

   
   while (1) {
      switch (SRGP_waitEvent (INDEFINITE)) {
       case KEYBOARD:
	 SRGP_getDeluxeKeyboard (&dkm);
	 DisplayKeyboardMeasure();
	 if (dkm.buffer[0] == 'q') {
	    SRGP_end();
	    exit(0);
	 }
      }
   }
}
