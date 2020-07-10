#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>

#include "srgp.h"

struct srgp_global_state {
    int width;
    int height;
    Display* display;
    Window window;
    GC gc;
};

// Global state is unavoidable when maintaining API compatibility.
// Keeping it all in one spot at least makes it easier to track.
static struct srgp_global_state _state;

#define FLIP_VERT(x) (_state.height - (x))
#define FLIP_HORIZ(x) (_state.width - (x))

int
x11_error_handler(Display* display, XErrorEvent* e)
{
    char buf[1024] = { 0 };
    XGetErrorText(e->display, e->error_code, buf, sizeof(buf));
    fprintf(stderr, "x11 error: %s\n", buf);
    return 0;
}

void
SRGP_begin(char* name, int w, int h, int planes, bool trace)
{
    _state.width = w;
    _state.height = h;

    _state.display = XOpenDisplay(NULL);
    assert(_state.display != NULL);

    XSetErrorHandler(x11_error_handler);

    int screen = XDefaultScreen(_state.display);
    int black = XBlackPixel(_state.display, screen);
    int white = XWhitePixel(_state.display, screen);

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
    assert(font_info);

    XGCValues gc_values = {
        .font = font_info->fid,
        .foreground = black,
    };

    _state.gc = XCreateGC(_state.display, _state.window, 0, &gc_values);
    XSetForeground(_state.display, _state.gc, black);

    XSelectInput(_state.display, _state.window, StructureNotifyMask);
    XMapWindow(_state.display, _state.window);

    while (true) {
        XEvent ev;
        XNextEvent(_state.display, &ev);
        if (ev.type == MapNotify) {
            break;
        }
    }
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
    XDrawLine(_state.display, _state.window, _state.gc, x1, FLIP_VERT(y1), x2, FLIP_VERT(y2));
    XFlush(_state.display);
}

void
SRGP_line(point pt1, point pt2)
{
    SRGP_lineCoord(pt1.x, pt1.y, pt2.x, pt2.y);
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

//point
//SRGP_defPoint(int x, int y)
//{
//    point p = { x, y };
//    return p;
//}
//
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
