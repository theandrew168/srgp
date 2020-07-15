#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>

#include "srgp.h"

#define DASH_COUNT 4
#define DASH_ELEMENTS 4
static const char DASH_TABLE[DASH_COUNT][DASH_ELEMENTS] = {
    [CONTINUOUS] = {  0,  0,  0,  0 },
    [DASHED]     = { 10,  5, 10,  5 },
    [DOTTED]     = {  4,  4,  4,  4 },
    [DOT_DASHED] = { 12,  4,  4,  4 },
};

#define BITMAP_COUNT 105
#define BITMAP_ELEMENTS 8
static const unsigned char BITMAP_TABLE[BITMAP_COUNT][BITMAP_ELEMENTS] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
    { 0x7f, 0xff, 0xf7, 0xff, 0x7f, 0xff, 0xf7, 0xff },
    { 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77 },
    { 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 },
    { 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff },
    { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa },
    { 0xee, 0xdd, 0xbb, 0x77, 0xee, 0xdd, 0xbb, 0x77 },
    { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88 },
    { 0xb1, 0x30, 0x03, 0x1b, 0xd8, 0xc0, 0x0c, 0x8d },
    { 0x80, 0x10, 0x02, 0x20, 0x01, 0x08, 0x40, 0x04 },
    { 0xff, 0x88, 0x88, 0x88, 0xff, 0x88, 0x88, 0x88 },
    { 0xff, 0x80, 0x80, 0x80, 0xff, 0x08, 0x08, 0x08 },
    { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x80, 0x40, 0x20, 0x00, 0x02, 0x04, 0x08, 0x00 },
    { 0x82, 0x44, 0x39, 0x44, 0x82, 0x01, 0x01, 0x01 },
    { 0xf8, 0x74, 0x22, 0x47, 0x8f, 0x17, 0x22, 0x71 },
    { 0x55, 0xa0, 0x40, 0x40, 0x55, 0x0a, 0x04, 0x04 },
    { 0x20, 0x50, 0x88, 0x88, 0x88, 0x88, 0x05, 0x02 },
    { 0xbf, 0x00, 0xbf, 0xbf, 0xb0, 0xb0, 0xb0, 0xb0 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x80, 0x00, 0x08, 0x00, 0x80, 0x00, 0x08, 0x00 },
    { 0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0x22, 0x00 },
    { 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22 },
    { 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00 },
    { 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00 },
    { 0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88 },
    { 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00 },
    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 },
    { 0xaa, 0x00, 0x80, 0x00, 0x88, 0x00, 0x80, 0x00 },
    { 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },
    { 0x08, 0x1c, 0x22, 0xc1, 0x80, 0x01, 0x02, 0x04 },
    { 0x88, 0x14, 0x22, 0x41, 0x88, 0x00, 0xaa, 0x00 },
    { 0x40, 0xa0, 0x00, 0x00, 0x04, 0x0a, 0x00, 0x00 },
    { 0x03, 0x84, 0x48, 0x30, 0x0c, 0x02, 0x01, 0x01 },
    { 0x80, 0x80, 0x41, 0x3e, 0x08, 0x08, 0x14, 0xe3 },
    { 0x10, 0x20, 0x54, 0xaa, 0xff, 0x02, 0x04, 0x08 },
    { 0x77, 0x89, 0x8f, 0x8f, 0x77, 0x98, 0xf8, 0xf8 },
    { 0x00, 0x08, 0x14, 0x2a, 0x55, 0x2a, 0x14, 0x08 },
    { 0x00, 0x08, 0x14, 0x2a, 0x55, 0x2a, 0x14, 0x08 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 },
    { 0x88, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 },
    { 0x88, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00 },
    { 0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x00, 0x00 },
    { 0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x02, 0x00 },
    { 0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0x02, 0x00 },
    { 0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0x22, 0x00 },
    { 0xa8, 0x00, 0x22, 0x00, 0x88, 0x00, 0x22, 0x00 },
    { 0xa8, 0x00, 0x22, 0x00, 0x8a, 0x00, 0x22, 0x00 },
    { 0xaa, 0x00, 0x22, 0x00, 0x8a, 0x00, 0x22, 0x00 },
    { 0xaa, 0x00, 0x22, 0x00, 0xaa, 0x00, 0x22, 0x00 },
    { 0xaa, 0x00, 0xa2, 0x00, 0xaa, 0x00, 0x22, 0x00 },
    { 0xaa, 0x00, 0xa2, 0x00, 0xaa, 0x00, 0x2a, 0x00 },
    { 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0x2a, 0x00 },
    { 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00 },
    { 0xaa, 0x40, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00 },
    { 0xaa, 0x40, 0xaa, 0x00, 0xaa, 0x04, 0xaa, 0x00 },
    { 0xaa, 0x44, 0xaa, 0x00, 0xaa, 0x04, 0xaa, 0x00 },
    { 0xaa, 0x44, 0xaa, 0x00, 0xaa, 0x44, 0xaa, 0x00 },
    { 0xaa, 0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x00 },
    { 0xaa, 0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x01 },
    { 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x01 },
    { 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11 },
    { 0xaa, 0x54, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11 },
    { 0xaa, 0x54, 0xaa, 0x11, 0xaa, 0x45, 0xaa, 0x11 },
    { 0xaa, 0x55, 0xaa, 0x11, 0xaa, 0x45, 0xaa, 0x11 },
    { 0xaa, 0x55, 0xaa, 0x11, 0xaa, 0x55, 0xaa, 0x11 },
    { 0xaa, 0x55, 0xaa, 0x51, 0xaa, 0x55, 0xaa, 0x11 },
    { 0xaa, 0x55, 0xaa, 0x51, 0xaa, 0x55, 0xaa, 0x15 },
    { 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x15 },
    { 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 },
    { 0xea, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 },
    { 0xea, 0x55, 0xaa, 0x55, 0xae, 0x55, 0xaa, 0x55 },
    { 0xee, 0x55, 0xaa, 0x55, 0xae, 0x55, 0xaa, 0x55 },
    { 0xee, 0x55, 0xaa, 0x55, 0xee, 0x55, 0xaa, 0x55 },
    { 0xee, 0x55, 0xba, 0x55, 0xee, 0x55, 0xaa, 0x55 },
    { 0xee, 0x55, 0xba, 0x55, 0xee, 0x55, 0xab, 0x55 },
    { 0xee, 0x55, 0xbb, 0x55, 0xee, 0x55, 0xab, 0x55 },
    { 0xee, 0x55, 0xbb, 0x55, 0xee, 0x55, 0xbb, 0x55 },
    { 0xfe, 0x55, 0xbb, 0x55, 0xee, 0x55, 0xbb, 0x55 },
    { 0xfe, 0x55, 0xbb, 0x55, 0xef, 0x55, 0xbb, 0x55 },
    { 0xff, 0x55, 0xbb, 0x55, 0xef, 0x55, 0xbb, 0x55 },
    { 0xff, 0x55, 0xbb, 0x55, 0xff, 0x55, 0xbb, 0x55 },
    { 0xff, 0x55, 0xfb, 0x55, 0xff, 0x55, 0xbb, 0x55 },
    { 0xff, 0x55, 0xfb, 0x55, 0xff, 0x55, 0xbf, 0x55 },
    { 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xbf, 0x55 },
    { 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55 },
    { 0xff, 0xd5, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55 },
    { 0xff, 0xd5, 0xff, 0x55, 0xff, 0x5d, 0xff, 0x55 },
    { 0xff, 0xdd, 0xff, 0x55, 0xff, 0x5d, 0xff, 0x55 },
    { 0xff, 0xdd, 0xff, 0x55, 0xff, 0xdd, 0xff, 0x55 },
    { 0xff, 0xdd, 0xff, 0x75, 0xff, 0xdd, 0xff, 0x55 },
    { 0xff, 0xdd, 0xff, 0x75, 0xff, 0xdd, 0xff, 0x57 },
    { 0xff, 0xdd, 0xff, 0x77, 0xff, 0xdd, 0xff, 0x57 },
    { 0xff, 0xdd, 0xff, 0x77, 0xff, 0xdd, 0xff, 0x77 },
    { 0xff, 0xfd, 0xff, 0x77, 0xff, 0xdd, 0xff, 0x77 },
    { 0xff, 0xfd, 0xff, 0x77, 0xff, 0xdf, 0xff, 0x77 },
    { 0xff, 0xff, 0xff, 0x77, 0xff, 0xdf, 0xff, 0x77 },
    { 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff, 0x77 },
    { 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0x77 },
    { 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0x7f },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
};

#define PIXMAP_COUNT 1
#define PIXMAP_ELEMENTS 8
static const unsigned char PIXMAP_TABLE[PIXMAP_COUNT][PIXMAP_ELEMENTS] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

typedef struct {
//    int writeMode;
//    rectangle clipRectangle;
    int font;
    lineStyle lineStyle;
    int lineWidth;
    int markerSize;
    markerStyle markerStyle;
    int colorIndex;
    int backgroundColorIndex;
//    int planeMask;
    drawStyle fillStyle;
    int fillPixmapPatternId;
    int fillBitmapPatternId;
//    drawStyle penStyle;
//    int penPixmapPatternId;
//    int penBitmapPatternId;
} attributeGroup;

struct srgpGlobalState {
    int width;
    int height;
    Display* display;
    Window window;
    GC gc;

//    XFontStruct* font_8x13;
    attributeGroup attributes;
    Pixmap bitmaps[BITMAP_COUNT];
    Pixmap pixmaps[PIXMAP_COUNT];
};

// Global state is unavoidable when maintaining API compatibility.
// Keeping it all in one spot at least makes it easier to track.
static struct srgpGlobalState _state = { 0 };

#define FLIP_VERT(x) (_state.height - (x))
#define FLIP_HORIZ(x) (_state.width - (x))

static void
set_attrib_defaults(void)
{
    SRGP_setMarkerSize(10);
    SRGP_setMarkerStyle(MARKER_CIRCLE);
    SRGP_setLineStyle(CONTINUOUS);
    SRGP_setLineWidth(1);
    SRGP_setColor(COLOR_BLACK);
    SRGP_setBackgroundColor(COLOR_WHITE);
    SRGP_setFillStyle(SOLID);
    SRGP_setFillBitmapPattern(0);
    SRGP_setFillPixmapPattern(0);
}

static int
x11_error_handler(Display* display, XErrorEvent* e)
{
    char buf[1024] = { 0 };
    XGetErrorText(e->display, e->error_code, buf, sizeof(buf));
    fprintf(stderr, "x11 error: %s\n", buf);
    return 0;
}

static void
x11_draw_circle_marker(int x, int y)
{
    int offset = _state.attributes.markerSize / 2;
    XDrawArc(
        _state.display, _state.window, _state.gc,
        x - offset, FLIP_VERT(y) - offset,
        _state.attributes.markerSize,
        _state.attributes.markerSize,
        0, 360 * 64);
    XFlush(_state.display);
}

static void
x11_draw_square_marker(int x, int y)
{
    int offset = _state.attributes.markerSize / 2;
    XDrawRectangle(
        _state.display, _state.window, _state.gc,
        x - offset, FLIP_VERT(y) - offset,
        _state.attributes.markerSize,
        _state.attributes.markerSize);
    XFlush(_state.display);
}

static void
x11_draw_x_marker(int x, int y)
{
    int offset = _state.attributes.markerSize / 2;
    XDrawLine(
        _state.display, _state.window, _state.gc,
        x - offset, FLIP_VERT(y) - offset, x + offset, FLIP_VERT(y) + offset);
    XDrawLine(
        _state.display, _state.window, _state.gc,
        x - offset, FLIP_VERT(y) + offset, x + offset, FLIP_VERT(y) - offset);
    XFlush(_state.display);
}

void
SRGP_begin(char* name, int w, int h, int planes, boolean trace)
{
    _state.width = w;
    _state.height = h;

    _state.display = XOpenDisplay(NULL);
    assert(_state.display != NULL);

    XSetErrorHandler(x11_error_handler);

    int screen = XDefaultScreen(_state.display);
    int white = XWhitePixel(_state.display, screen);
    int black = XBlackPixel(_state.display, screen);

    _state.window = XCreateSimpleWindow(
        _state.display,
        XRootWindow(_state.display, screen),
        0,
        0,
        _state.width,
        _state.height,
        0,
        white,
        white);

    // init bitmaps
    for (long i = 0; i < BITMAP_COUNT; i++) {
        _state.bitmaps[i] = XCreateBitmapFromData(_state.display, _state.window, (char*)BITMAP_TABLE[i], 8, 8);
        if (_state.bitmaps[i] == None) {
            fprintf(stderr, "uh oh failed bitmap alloc :(\n");
        }
    }

    // init pixmaps
    for (long i = 0; i < PIXMAP_COUNT; i++) {
        _state.pixmaps[i] = XCreatePixmapFromBitmapData(
            _state.display, _state.window,
            (char*)PIXMAP_TABLE[i], 8, 8,
            black, white,
            1);  // TODO: depth should be variable
    }

    // set window name
    XStoreName(_state.display, _state.window, name);

//    _state.font_8x13 = XLoadQueryFont(_state.display, "8x13");
//    assert(_state.font_8x13 != NULL);

    XGCValues gc_values = {
//        .font = _state.font_8x13->fid,
        .foreground = black,
    };

    _state.gc = XCreateGC(_state.display, _state.window, 0, &gc_values);
    XSetForeground(_state.display, _state.gc, black);

    XSelectInput(_state.display, _state.window, StructureNotifyMask);
    XMapWindow(_state.display, _state.window);

    for (;;) {
        XEvent ev;
        XNextEvent(_state.display, &ev);
        if (ev.type == MapNotify) {
            break;
        }
    }

    set_attrib_defaults();
}

void
SRGP_end(void)
{
    // free bitmaps
    for (long i = 0; i < BITMAP_COUNT; i++) {
        XFreePixmap(_state.display, _state.bitmaps[i]);
    }

    // free pixmaps
    for (long i = 0; i < PIXMAP_COUNT; i++) {
        XFreePixmap(_state.display, _state.pixmaps[i]);
    }

//    XFreeFont(_state.display, _state.font_8x13);

    XFreeGC(_state.display, _state.gc);
    XDestroyWindow(_state.display, _state.window);
    XCloseDisplay(_state.display);
}

void
SRGP_lineCoord(int x1, int y1, int x2, int y2)
{
    XDrawLine(
        _state.display, _state.window, _state.gc,
        x1, FLIP_VERT(y1), x2, FLIP_VERT(y2));
    XFlush(_state.display);
}

void
SRGP_line(point pt1, point pt2)
{
    XDrawLine(
        _state.display, _state.window, _state.gc,
        pt1.y, FLIP_VERT(pt1.y), pt2.x, FLIP_VERT(pt2.y));
    XFlush(_state.display);
}

void
SRGP_polyLineCoord(int vertexCount, int* xArray, int* yArray)
{
    XPoint* points = malloc(vertexCount * sizeof(XPoint));
    for (long i = 0; i < vertexCount; i++) {
        points[i].x = xArray[i];
        points[i].y = FLIP_VERT(yArray[i]);
    }

    XDrawLines(_state.display, _state.window, _state.gc, points, vertexCount, CoordModeOrigin);
    XFlush(_state.display);

    free(points);
}

void
SRGP_polyLine(int vertexCount, point* vertices)
{
    XPoint* points = malloc(vertexCount * sizeof(XPoint));
    for (long i = 0; i < vertexCount; i++) {
        points[i].x = vertices[i].x;
        points[i].y = FLIP_VERT(vertices[i].y);
    }

    XDrawLines(_state.display, _state.window, _state.gc, points, vertexCount, CoordModeOrigin);
    XFlush(_state.display);

    free(points);
}

void
SRGP_markerCoord(int x, int y)
{
    switch (_state.attributes.markerStyle) {
        case MARKER_CIRCLE: x11_draw_circle_marker(x, y); break;
        case MARKER_SQUARE: x11_draw_square_marker(x, y); break;
        case MARKER_X: x11_draw_x_marker(x, y); break;
    }
}

void
SRGP_marker(point pt)
{
    switch (_state.attributes.markerStyle) {
        case MARKER_CIRCLE: x11_draw_circle_marker(pt.x, pt.y); break;
        case MARKER_SQUARE: x11_draw_square_marker(pt.x, pt.y); break;
        case MARKER_X: x11_draw_x_marker(pt.x, pt.y); break;
    }
}

void
SRGP_polyMarkerCoord(int vertexCount, int* xArray, int* yArray)
{
    while (vertexCount--) {
        switch (_state.attributes.markerStyle) {
            case MARKER_CIRCLE: x11_draw_circle_marker(*xArray, *yArray); break;
            case MARKER_SQUARE: x11_draw_square_marker(*xArray, *yArray); break;
            case MARKER_X: x11_draw_x_marker(*xArray, *yArray); break;
        }
        xArray++;
        yArray++;
    }
}

void
SRGP_polyMarker(int vertexCount, point* vertices)
{
    while (vertexCount--) {
        switch (_state.attributes.markerStyle) {
            case MARKER_CIRCLE: x11_draw_circle_marker(vertices->x, vertices->y); break;
            case MARKER_SQUARE: x11_draw_square_marker(vertices->x, vertices->y); break;
            case MARKER_X: x11_draw_x_marker(vertices->x, vertices->y); break;
        }
        vertices++;
    }
}

void
SRGP_polygon(int vertexCount, point* vertices)
{
    SRGP_polyLine(vertexCount, vertices);
    SRGP_line(vertices[0], vertices[vertexCount - 1]);
}

void
SRGP_rectangleCoord(int leftX, int bottomY, int rightX, int topY)
{
    XDrawRectangle(
        _state.display, _state.window, _state.gc,
        leftX, FLIP_VERT(topY), rightX - leftX, topY - bottomY);
    XFlush(_state.display);
}

void
SRGP_rectanglePt(point bottomLeft, point topRight)
{
    SRGP_rectangleCoord(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);
}

void
SRGP_rectangle(rectangle rect)
{
    SRGP_rectangleCoord(rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
}

point
SRGP_defPoint(int x, int y)
{
    point p = { x, y };
    return p;
}

rectangle
SRGP_defRectangle(int leftX, int bottomY, int rightX, int topY)
{
    rectangle r = {
        .bottomLeft = { leftX, bottomY },
        .topRight = { rightX, topY },
    };
    return r;
}

void
SRGP_ellipseArc(rectangle extentRect, double startAngle, double endAngle)
{
    int xangle1, xangle2;
    if (startAngle <= endAngle) {
        xangle1 = startAngle * 64;
        xangle2 = (endAngle - startAngle) * 64;
    } else {
        xangle1 = endAngle * 64;
        xangle2 = (startAngle - 360 - endAngle) * 64;
    }

    XDrawArc(
        _state.display, _state.window, _state.gc,
        extentRect.bottomLeft.x,
        FLIP_VERT(extentRect.topRight.y),
        extentRect.topRight.x - extentRect.bottomLeft.x,
        extentRect.topRight.y - extentRect.bottomLeft.y,
        xangle1, xangle2);
    XFlush(_state.display);
}

void
SRGP_setLineStyle(lineStyle lineStyle)
{
    if (_state.attributes.lineStyle == lineStyle) return;
    _state.attributes.lineStyle = lineStyle;

    if (_state.attributes.lineStyle != CONTINUOUS) {
        XSetDashes(_state.display, _state.gc, 0, DASH_TABLE[lineStyle], DASH_ELEMENTS);
    }

    XSetLineAttributes(
        _state.display, _state.gc,
        _state.attributes.lineWidth,
        _state.attributes.lineStyle == CONTINUOUS ? LineSolid : LineOnOffDash,
        CapButt,
        JoinBevel);
}

void
SRGP_setLineWidth(int width)
{
    if (_state.attributes.lineWidth == width) return;
    _state.attributes.lineWidth = width;

    XSetLineAttributes(
        _state.display, _state.gc,
        _state.attributes.lineWidth,
        _state.attributes.lineStyle == CONTINUOUS ? LineSolid : LineOnOffDash,
        CapButt,
        JoinBevel);
}

void
SRGP_setMarkerSize(int markerSize)
{
    if (_state.attributes.markerSize == markerSize) return;
    _state.attributes.markerSize = markerSize;
}

void
SRGP_setMarkerStyle(markerStyle markerStyle)
{
    if (_state.attributes.markerStyle == markerStyle) return;
    _state.attributes.markerStyle = markerStyle;
}

void
SRGP_setColor(int colorIndex)
{
    if (_state.attributes.colorIndex == colorIndex) return;
    _state.attributes.colorIndex = colorIndex;

    int screen = XDefaultScreen(_state.display);
    int white = XWhitePixel(_state.display, screen);
    int black = XBlackPixel(_state.display, screen);

    if (colorIndex == COLOR_WHITE) {
        XSetForeground(_state.display, _state.gc, white);
    } else if (colorIndex == COLOR_BLACK) {
        XSetForeground(_state.display, _state.gc, black);
    }
}

void
SRGP_setBackgroundColor(int colorIndex)
{
    if (_state.attributes.backgroundColorIndex == colorIndex) return;
    _state.attributes.backgroundColorIndex = colorIndex;

    int screen = XDefaultScreen(_state.display);
    int white = XWhitePixel(_state.display, screen);
    int black = XBlackPixel(_state.display, screen);

    if (colorIndex == COLOR_WHITE) {
        XSetBackground(_state.display, _state.gc, white);
    } else if (colorIndex == COLOR_BLACK) {
        XSetBackground(_state.display, _state.gc, black);
    }
}

void
SRGP_setFillStyle(drawStyle drawStyle)
{
    if (_state.attributes.fillStyle == drawStyle) return;
    _state.attributes.fillStyle = drawStyle;

    XSetFillStyle(_state.display, _state.gc, drawStyle);
}

void
SRGP_setFillBitmapPattern(int patternIndex)
{
    if (_state.attributes.fillBitmapPatternId == patternIndex) return;
    _state.attributes.fillBitmapPatternId = patternIndex;

    XSetStipple(_state.display, _state.gc, _state.bitmaps[patternIndex]);
}

void
SRGP_setFillPixmapPattern(int patternIndex)
{
    if (_state.attributes.fillPixmapPatternId == patternIndex) return;
    _state.attributes.fillPixmapPatternId = patternIndex;

    XGCValues gcvals = {
        .tile = _state.pixmaps[patternIndex],
    };
    XChangeGC(_state.display, _state.gc, GCTile, &gcvals);
}

void
SRGP_fillPolygon(int vertexCount, point* vertices)
{
    XPoint* points = malloc(vertexCount * sizeof(XPoint));
    for (long i = 0; i < vertexCount; i++) {
        points[i].x = vertices[i].x;
        points[i].y = FLIP_VERT(vertices[i].y);
    }

    XFillPolygon(
        _state.display, _state.window, _state.gc,
        points, vertexCount,
        Complex, CoordModeOrigin);
    XFlush(_state.display);

    free(points);
}

void
SRGP_fillEllipseArc(rectangle extentRect, double startAngle, double endAngle)
{
    int xangle1, xangle2;
    if (startAngle <= endAngle) {
        xangle1 = startAngle * 64;
        xangle2 = (endAngle - startAngle) * 64;
    } else {
        xangle1 = endAngle * 64;
        xangle2 = (startAngle - 360 - endAngle) * 64;
    }

    XFillArc(
        _state.display, _state.window, _state.gc,
        extentRect.bottomLeft.x,
        FLIP_VERT(extentRect.topRight.y),
        extentRect.topRight.x - extentRect.bottomLeft.x,
        extentRect.topRight.y - extentRect.bottomLeft.y,
        xangle1, xangle2);
    XFlush(_state.display);
}

void
SRGP_fillEllipse(rectangle extentRect)
{
    SRGP_fillEllipseArc(extentRect, 0.0, 360.0);
}

void
SRGP_fillRectangleCoord(int leftX, int bottomY, int rightX, int topY)
{
    XFillRectangle(
        _state.display, _state.window, _state.gc,
        leftX, FLIP_VERT(topY), rightX - leftX + 1, topY - bottomY + 1);
    XFlush(_state.display);
}

void
SRGP_fillRectangle(rectangle rect)
{
    SRGP_fillRectangleCoord(rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
}

void
SRGP_beep(void)
{
    XBell(_state.display, 0);
}

void
SRGP_polygonCoord(int vertexCount, int* xArray, int* yArray)
{
    SRGP_polyLineCoord(vertexCount, xArray, yArray);
    SRGP_lineCoord(xArray[0], yArray[0], xArray[vertexCount - 1], yArray[vertexCount - 1]);
}

void
SRGP_fillPolygonCoord(int vertexCount, int* xArray, int* yArray)
{
    XPoint* points = malloc(vertexCount * sizeof(XPoint));
    for (long i = 0; i < vertexCount; i++) {
        points[i].x = xArray[i];
        points[i].y = FLIP_VERT(yArray[i]);
    }

    XFillPolygon(
        _state.display, _state.window, _state.gc,
        points, vertexCount,
        Complex, CoordModeOrigin);
    XFlush(_state.display);

    free(points);
}

void
SRGP_ellipse(rectangle extentRect)
{
    SRGP_ellipseArc(extentRect, 0.0, 360.0);
}

void
SRGP_fillRectanglePt(point bottomLeft, point topRight)
{
    SRGP_fillRectangleCoord(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);
}

//void
//SRGP_text(point origin, char* str)
//{
//    XSetFillStyle(
//        _state.display,
//        _state.gc,
//        SOLID);
//    XDrawString(
//        _state.display,
//        _state.window,
//        _state.gc,
//        origin.x,
//        _state.height - origin.y,
//        str,
//        strlen(str));
//    XFlush(_state.display);
//}
