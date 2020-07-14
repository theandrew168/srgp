#ifndef SRGP_SRGP_H_INCLUDED
#define SRGP_SRGP_H_INCLUDED

typedef unsigned char boolean;
#define TRUE  1
#define FALSE 0

#define COLOR_WHITE 0
#define COLOR_BLACK 1

typedef enum {
    CONTINUOUS = 0,
    DASHED,
    DOTTED,
    DOT_DASHED,
} lineStyle;

typedef enum {
    MARKER_CIRCLE = 0,
    MARKER_SQUARE,
    MARKER_X,
} markerStyle;

//typedef enum {
//    SOLID = 0,
//    PIXMAP_PATTERN,
//    BITMAP_PATTERN_TRANSPARENT,
//    BITMAP_PATTERN_OPAQUE,
//} drawStyle;

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point bottomLeft;
    point topRight;
} rectangle;

// Baseline stuff inferred from Tronche's tutorial
void SRGP_begin(char* name, int w, int h, int planes, boolean trace);
void SRGP_end(void);

// Lines and polylines (page 27)
void SRGP_lineCoord(int x1, int y1, int x2, int y2);
void SRGP_line(point pt1, point pt2);
void SRGP_polyLineCoord(int vertexCount, int* xArray, int* yArray);
void SRGP_polyLine(int vertexCount, point* vertices);

// Markers and polymarkers (page 28-29)
void SRGP_markerCoord(int x, int y);
void SRGP_marker(point pt);
void SRGP_polyMarkerCoord(int vertexCount, int* xArray, int* yArray);
void SRGP_polyMarker(int vertexCount, point* vertices);

// Polygons and rectangles (page 29-30)
void SRGP_polygon(int vertexCount, point* vertices);
void SRGP_rectangleCoord(int leftX, int bottomY, int rightX, int topY);
void SRGP_rectanglePt(point bottomLeft, point topRight);
void SRGP_rectangle(rectangle rect);
point SRGP_defPoint(int x, int y);
rectangle SRGP_defRectangle(int leftX, int bottomY, int rightX, int topY);

// Circles and ellipses (page 30-31)
void SRGP_ellipseArc(rectangle extentRect, double startAngle, double endAngle);

// Line style and line width (page 31-32)
void SRGP_setLineStyle(int lineStyle);
void SRGP_setLineWidth(int width);
void SRGP_setMarkerSize(int markerSize);
void SRGP_setMarkerStyle(int markerStyle);

// Color (page 32-33)
void SRGP_setColor(int colorIndex);

//void SRGP_text(point origin, char* str);
//void SRGP_beep(void);
//void SRGP_setFillStyle(drawStyle value);
//void SRGP_setFillBitmapPattern(int value);
//void SRGP_fillRectangleCoord(int left_x, int bottom_y, int right_x, int top_y);

#endif
