#include <stdbool.h>

enum {
    TRUE = true,
    FALSE = false,
};

typedef enum {
    SOLID = 0,
    PIXMAP_PATTERN,
    BITMAP_PATTERN_TRANSPARENT,
    BITMAP_PATTERN_OPAQUE,
} drawStyle;

typedef struct point {
    int x;
    int y;
} point;

typedef struct rectangle {
    point bottomLeft;
    point topRight;
} rectangle;

void SRGP_begin(char* name, int w, int h, int planes, bool trace);
void SRGP_end(void);

// Lines and polylines (page 27)
void SRGP_lineCoord(int x1, int y1, int x2, int y2);
void SRGP_line(point pt1, point pt2);
void SRGP_polyLineCoord(int vertexCount, int* xArray, int* yArray);
void SRGP_polyLine(int vertexCount, point* vertices);

//point SRGP_defPoint(int x, int y);
//void SRGP_text(point origin, char* str);
//void SRGP_beep(void);
//void SRGP_setFillStyle(drawStyle value);
//void SRGP_setFillBitmapPattern(int value);
//void SRGP_fillRectangleCoord(int left_x, int bottom_y, int right_x, int top_y);
