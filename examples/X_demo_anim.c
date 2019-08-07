/*************** ELECTRONIC VUGRAF ROUTINES
The top part of this file contains general-purpose routines suitable
for creating an animated demonstration of SRGP functionality.
*/

#include "srgp.h"
#ifdef THINK_C
#include <unix.h>
#include <stdlib.h>
#endif

#define EVU_DO(STATEMENT)   EVUprint(#STATEMENT ";"); STATEMENT

static attribute_group bund;

static int frame_announcement_y, code_reset_y, ycoord, ydelta;

static void
EVUdetermineTextInfo (void)
{
   int w, h, d;
   int wd, ht;

   SRGP_inquireTextExtent ("hello", &w, &h, &d);
   ydelta = h+d;
#ifndef THINK_C
   ydelta++;
#endif
   SRGP_inquireCanvasSize (0, &wd, &ht);
   frame_announcement_y = ht-h-1;
   code_reset_y = ycoord = ht-ydelta-ydelta;
}
   
   

static char buffer[80];


static void
EVUprint (char *text)
{
   SRGP_inquireAttributes (&bund);
   SRGP_setColor (COLOR_BLACK);
   SRGP_setWriteMode (WRITE_REPLACE);
   SRGP_setClipRectangle (SRGP_defRectangle(0,0,1023,799));
   SRGP_text (SRGP_defPoint(15,ycoord), text);
   ycoord -= ydelta;
   SRGP_setAttributes (&bund);
}

static void EVUvertspace(void)
{
   ycoord -= (ydelta>>1);
}


static void
EVUcomment (char *text)
{
   sprintf (buffer, "/* %s */", text);
   EVUprint (buffer);
}
   


static void
EVUframe(void)
{
   static int framenumber=0;
   int w, h, d;

   framenumber++;
   SRGP_inquireAttributes (&bund);
   SRGP_setClipRectangle (SRGP_defRectangle(0,0,1023,799));
   SRGP_setColor (COLOR_WHITE);
   SRGP_setFillStyle (SOLID);
   SRGP_setWriteMode (WRITE_REPLACE);
   SRGP_inquireTextExtent ("Frame #XXXX ", &w, &h, &d);
   SRGP_fillRectangle 
      (SRGP_defRectangle
	 (4, frame_announcement_y-d,
	  4+w, frame_announcement_y+h));
   sprintf (buffer, "Frame #%4d    ", framenumber);
   SRGP_setColor (COLOR_BLACK);
   SRGP_text (SRGP_defPoint(4,frame_announcement_y), buffer);
   SRGP_setAttributes (&bund);

   EVUvertspace();

   SRGP_waitEvent(-1);
}

static void
EVUbegin(void)
{
   char inpt[2];


   SRGP_begin ("SRGP Demonstration", 1024, 800, 3, FALSE);
   SRGP_setKeyboardProcessingMode (RAW);
   SRGP_setInputMode (KEYBOARD, EVENT);

#ifdef THINK_C
   SRGP_loadFont (0, "Geneva.9");
#endif

   EVUdetermineTextInfo ();

   SRGP_text (SRGP_defPoint(10,500), 
	      "An Introduction to SRGP");
   SRGP_text (SRGP_defPoint(10,470),
              "Any keystroke yields next frame of the sequence...");
   SRGP_waitEvent (-1);
}

static void
EVUclear(void)
{
   SRGP_inquireAttributes (&bund);
   SRGP_setColor (COLOR_WHITE);
   SRGP_setFillStyle (SOLID);
   SRGP_setWriteMode (WRITE_REPLACE);
   SRGP_setClipRectangle (SRGP_defRectangle(0,0,1023,799));
   SRGP_fillRectangleCoord (0,0, 1023,799);
   SRGP_setAttributes (&bund);
   ycoord = code_reset_y;
}


static void usleep (int n)
{
   while (n--);
}
   


static void makepatterns(void)
{   
   EVU_DO (SRGP_fillRectangleCoord (560,60, 940,540));
   EVU_DO (SRGP_setFillBitmapPattern (2));
   EVU_DO (SRGP_fillRectangleCoord (580,80, 920,520));
   EVU_DO (SRGP_setFillBitmapPattern (3));
   EVU_DO (SRGP_fillRectangleCoord (600,100, 900,500));
   EVU_DO (SRGP_setFillBitmapPattern (4));
   EVU_DO (SRGP_fillRectangleCoord (620,120, 880,480));
   EVU_DO (SRGP_setFillBitmapPattern (5));
   EVU_DO (SRGP_fillRectangleCoord (640,140, 860,460));
   EVU_DO (SRGP_setFillBitmapPattern (6));
   EVU_DO (SRGP_fillRectangleCoord (660,160, 840,440));
   EVU_DO (SRGP_setFillBitmapPattern (7));
   EVU_DO (SRGP_fillRectangleCoord (680,180, 820,420));
   EVU_DO (SRGP_setFillBitmapPattern (8));
   EVU_DO (SRGP_fillRectangleCoord (700,200, 800,400));
}


void SRGP__setCanvasDefaults (canvasID);


main()
{
   point bottomleft, topright, data[3], destination;
   static int xcoords[6]={100,200,300,400,500,600};
   static int ycoords[6]={105,240,270,378,118,20};
   rectangle largerect, cliprect;
   int numofplanes;
   long i;


   EVUbegin();
   EVUclear();

   EVUcomment ("The screen-canvas coordinate system has origin at lower-left");
   EVU_DO (SRGP_lineCoord (0,0, 1023,799));
   EVUframe();

   EVUcomment ("Drawing a single pixel");
   EVU_DO (SRGP_pointCoord (300,100));
   EVUframe();

   EVUcomment ("Clipping takes care of non-existent pixels");
   EVU_DO (SRGP_lineCoord (-50,-237, 1282,1888));
   EVUframe();
 
   EVUclear();

   EVUcomment ("Geometric data structures can be used if desired");
   EVUprint ("point bottomleft, topright;");
   EVUvertspace();
   EVU_DO (bottomleft = SRGP_defPoint (0, 0));
   EVU_DO (topright = SRGP_defPoint (1023, 799));
   EVU_DO (SRGP_line (bottomleft, topright));
   EVUframe();


   EVUprint ("rectangle largerect;");
   EVUvertspace();
   EVU_DO (largerect = SRGP_defRectangle (750,100, 1000,600));
   EVU_DO (SRGP_rectangle (largerect));
   EVU_DO (SRGP_rectangleCoord (600,25, 800,120));
   EVUframe();

   EVUclear();

   EVUcomment ("Attributes affect the appearance of primitives");
   EVU_DO (SRGP_setLineStyle (DASHED));
   EVU_DO (SRGP_ellipse (largerect));
   EVUframe();

   EVU_DO (SRGP_setLineWidth (10));
   EVU_DO (SRGP_ellipseArc (largerect, 45, 270));
   EVUframe();

   EVUcomment ("Pen style affects framed (outline) primitives");
   EVU_DO (SRGP_setPenStyle (BITMAP_PATTERN_OPAQUE));
   EVU_DO (SRGP_setPenBitmapPattern (26));
   EVU_DO (SRGP_ellipseArc (largerect, 270, 45));
   EVUframe();

   EVUclear();

   EVUcomment ("Fill style affects filled primitives");
   EVU_DO (SRGP_fillRectangle (largerect));
   EVU_DO (SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE));
   EVU_DO (SRGP_setFillBitmapPattern (23));
   EVU_DO (SRGP_fillRectangleCoord (700,25, 800,120));
   EVUframe();

   EVU_DO (SRGP_setFillBitmapPattern (6));
   EVU_DO (SRGP_fillEllipse (largerect));
   EVUframe();

   EVUclear();

   EVUcomment ("Let's reset attributes to normal...");
   EVU_DO (SRGP_setPenStyle (SOLID));
   EVU_DO (SRGP_setFillStyle (SOLID));
   EVU_DO (SRGP_setLineStyle (CONTINUOUS));
   EVU_DO (SRGP_setLineWidth (1));
   EVUvertspace();
   EVUcomment ("Primitives can be generated using data structures");
   EVUprint ("int xcoords[6], ycoords[6];");
   EVUprint ("point data[3];");
   EVUvertspace();
   EVUcomment ("Assume arrays have been initialized");
   EVU_DO (SRGP_polyLineCoord (6, xcoords, ycoords));
   EVUframe();

   data[0]=SRGP_defPoint(600,300);
   data[1]=SRGP_defPoint(800,600);
   data[2]=SRGP_defPoint(1000,400);
   EVU_DO (SRGP_polyLine (3, data));
   EVUframe();

   EVUprint ("/* polygon = polyline + (line joining 1st and last vertex) */");
   EVU_DO (SRGP_polygon (3, data));
   EVUframe();

   EVU_DO (SRGP_fillPolygon (3, data));
   EVUframe();

   EVUclear();


   EVUclear();

   EVUcomment ("Default clip rectangle is entire screen");
   EVU_DO (cliprect = SRGP_inquireClipRectangle());
   EVU_DO (SRGP_setLineStyle (DASHED));
   EVU_DO (SRGP_rectangle (cliprect));
   EVU_DO (SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE));
   makepatterns();
   EVUframe();
                
   EVUclear();

   EVUcomment ("Application can control the clip rectangle");
   EVU_DO (cliprect = SRGP_defRectangle (500,0, 850,500));
   EVU_DO (SRGP_setClipRectangle (cliprect));
   EVU_DO (SRGP_rectangle (cliprect));
   EVUframe();

   EVUcomment ("The effect of the clip rectangle");
   EVU_DO (SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE));
   makepatterns();
   EVUframe();
   EVUclear();

   SRGP__setCanvasDefaults (SCREEN_CANVAS);

   EVUcomment ("The write-mode attribute");
   EVU_DO (SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE));
   EVU_DO (SRGP_setFillBitmapPattern (12));
   EVU_DO (SRGP_fillRectangleCoord (0,100, 300,200));
   EVU_DO (SRGP_setFillBitmapPattern (7));
   EVU_DO (SRGP_fillRectangleCoord (100,0, 200,200));
   EVUframe();
 
   EVU_DO (SRGP_setWriteMode (WRITE_OR));
   EVU_DO (SRGP_setFillBitmapPattern (12));
   EVU_DO (SRGP_fillRectangleCoord (400,100, 700,200));
   EVU_DO (SRGP_setFillBitmapPattern (7));
   EVU_DO (SRGP_fillRectangleCoord (500,0, 600,200));
   EVUframe();
 
   EVU_DO (SRGP_setWriteMode (WRITE_XOR));
   EVU_DO (SRGP_setFillBitmapPattern (12));
   EVU_DO (SRGP_fillRectangleCoord (800,100, 1100,200));
   EVU_DO (SRGP_setFillBitmapPattern (7));
   EVU_DO (SRGP_fillRectangleCoord (900,0, 1000,200));
   EVUframe();

   EVUcomment ("XOR is used for reversible highlighting");
   EVU_DO (SRGP_setFillStyle (SOLID));
   EVU_DO (SRGP_setColor (COLOR_BLACK));
   EVU_DO (SRGP_fillRectangleCoord (0,0, 150,400));
   EVUframe();
   EVU_DO (SRGP_fillRectangleCoord (0,0, 150,400));
   EVUframe();

   EVUclear();

   EVUcomment ("The COPY-PIXEL operation");
   EVU_DO (SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE));
   EVU_DO (SRGP_setWriteMode (WRITE_REPLACE));
   makepatterns();
   EVUcomment ("Let's mark the source and destination");
   EVU_DO (SRGP_rectangle (largerect));
   EVU_DO (destination = SRGP_defPoint (480,300));
   EVU_DO (SRGP_marker (destination));
   EVUframe();

   EVU_DO (SRGP_copyPixel (SCREEN_CANVAS, largerect, destination));
   EVUframe();

   EVUcomment ("This copy goes off the screen");
   EVU_DO (destination = SRGP_defPoint (500,730));
   EVU_DO (SRGP_copyPixel (SCREEN_CANVAS, largerect, destination));
   EVUframe();

   EVUcomment ("This copy uses OR write-mode");
   EVU_DO (SRGP_setWriteMode (WRITE_OR));
   EVU_DO (destination = SRGP_defPoint (600,460));
   EVU_DO (SRGP_copyPixel (SCREEN_CANVAS, largerect, destination));
   EVUframe();

   EVUclear();

   numofplanes = SRGP_inquireCanvasDepth();
   if (numofplanes == 1) {
      EVUprint ("This is the end of the demo for non-color displays.");
      EVUprint ("Goodbye!");
      EVUframe();
      SRGP_end();
      exit(0);
   }

   EVUcomment ("Color lookup table is initially set to 0=white, 1=black");
   EVUcomment ("No other entries of table are preset");
   EVU_DO (SRGP_loadCommonColor (2, "LightSeaGreen"));
   EVU_DO (SRGP_loadCommonColor (3, "OrangeRed"));
   EVU_DO (SRGP_setColor (2));
   EVU_DO (SRGP_setWriteMode (WRITE_REPLACE));
   EVU_DO (SRGP_setFillStyle (SOLID));
   EVU_DO (SRGP_fillRectangleCoord (500,100, 800,200));
   EVUframe();
   EVUcomment ("foreground is now green, background still white");
   EVU_DO (SRGP_setFillStyle (BITMAP_PATTERN_OPAQUE));
   EVU_DO (SRGP_setFillBitmapPattern (16));
   EVU_DO (SRGP_fillRectangleCoord (530,130, 830,230));
   EVUframe();
   EVUcomment ("foreground is green, background is now orange-red");
   EVU_DO (SRGP_setBackgroundColor (3));
   EVU_DO (SRGP_fillRectangleCoord (560,160, 860,260));
   EVUframe();
   EVUcomment ("animation via color table modification");
   EVUcomment ("(warning: code actually being run is artificially slowed)");
   EVUprint ("for (i=0; i<30; i++) {");
   EVUprint ("   SRGP_loadCommonColor (0, \"OrangeRed\");");
   EVUprint ("   SRGP_loadCommonColor (0, \"White\");");
   EVUprint ("}");

   for (i=0; i<30; i++) {
       SRGP_loadCommonColor (0, "OrangeRed"); SRGP_refresh();
       usleep(60000);
       SRGP_loadCommonColor (0, "White"); SRGP_refresh();
       usleep(60000);
   }

   EVUcomment ("Finished!");
   EVUframe();

   EVUclear();
   EVUprint ("/********* Bye! ***********/");
   EVUframe();
 
   SRGP_end();
}
