#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>

#include "srgp.h"

#define DASH_ELEMENTS 4
static const char dashmap[][DASH_ELEMENTS] = {
    [CONTINUOUS] = {  0,  0,  0,  0 },
    [DASHED]     = { 10,  5, 10,  5 },
    [DOTTED]     = {  4,  4,  4,  4 },
    [DOT_DASHED] = { 12,  4,  4,  4 },
};

typedef struct {
//    int writeMode;
//    rectangle clipRectangle;
//    int font;
    int lineStyle;
    int lineWidth;
    int markerSize;
    int markerStyle;
    int colorIndex;
//    int backgroundColor;
//    int planeMask;
//    int fillStyle;
//    int fillPixmapPatternId;
//    int fillBitmapPatternId;
//    int penStyle;
//    int penPixmapPatternId;
//    int penBitmapPatternId;
} attributeGroup;

struct srgpGlobalState {
    int width;
    int height;
    Display* display;
    Window window;
    GC gc;

    attributeGroup attributes;
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

    XStoreName(_state.display, _state.window, name);

    XFontStruct* font_info = XLoadQueryFont(_state.display, "8x13");
    assert(font_info != NULL);

    XGCValues gc_values = {
        .font = font_info->fid,
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
SRGP_setLineStyle(int lineStyle)
{
    if (_state.attributes.lineStyle == lineStyle) return;
    _state.attributes.lineStyle = lineStyle;

    if (_state.attributes.lineStyle != CONTINUOUS) {
        XSetDashes(_state.display, _state.gc, 0, dashmap[lineStyle], DASH_ELEMENTS);
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
SRGP_setMarkerStyle(int markerStyle)
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
//
//void
//SRGP_beep(void)
//{
//    XBell(_state.display, 0);
//}
//
//void
//SRGP_setFillStyle(drawStyle value)
//{
//    XSetFillStyle(_state.display, _state.gc, value);
//}
//
//void
//SRGP_setFillBitmapPattern(int value)
//{
////    XSetStipple(_state.display, _state.gc, 
//}
//
//void
//SRGP_fillRectangleCoord(int left_x, int bottom_y, int right_x, int top_y)
//{
//    XFillRectangle(
//        _state.display,
//        _state.window,
//        _state.gc,
//        left_x,
//        _state.height - top_y,
//        right_x - left_x + 1,
//        top_y - bottom_y + 1);
//}
