/** SELECTING WHICH QUICKDRAW ROM TO USE
* There are four .c files that depend upon this .h file for determination
* of which ROM you are compiling for: the original monochrome QuickDraw ROM
* or the Color QuickDraw ROM.
*
* Below this comment, you should either have this line:
*		#define COLOR_QUICKDRAW
*	or:
*		#undef COLOR_QUICKDRAW
**/

#define COLOR_QUICKDRAW
