#include <stdbool.h>

#define TRUE true
#define FALSE false

typedef enum {
    SOLID = 0,
    PIXMAP_PATTERN,
    BITMAP_PATTERN_TRANSPARENT,
    BITMAP_PATTERN_OPAQUE,
} drawStyle;

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point bottomLeft;
    point topRight;
} rectangle;

point SRGP_defPoint(int x, int y);
void SRGP_text(point origin, char* str);
void SRGP_begin(char* name, int w, int h, int planes, bool trace);
void SRGP_end(void);
void SRGP_beep(void);
void SRGP_setFillStyle(drawStyle value);
void SRGP_setFillBitmapPattern(int value);
void SRGP_fillRectangleCoord(int left_x, int bottom_y, int right_x, int top_y);
