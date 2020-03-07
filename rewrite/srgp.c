#include "srgp.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <X11/Xlib.h>

#define UNUSED(x) (void)(x)

typedef struct {
    int width;
    int height;
    Display* display;
    Window window;
    GC gc;
} srgp_state;

// Global state is unavoidable when maintaining API compatibility.
// Keeping it all in one spot at least makes it easier to track.
static srgp_state _state;

point SRGP_defPoint(int x, int y)
{
    point p = { x, y };
    return p;
}

void SRGP_text(point origin, char* str)
{
    XSetFillStyle(
        _state.display,
        _state.gc,
        SOLID);
    XDrawString(
        _state.display,
        _state.window,
        _state.gc,
        origin.x,
        _state.height - origin.y,
        str,
        strlen(str));
    XFlush(_state.display);
}

void SRGP_begin(char* name, int w, int h, int planes, bool trace)
{
    UNUSED(planes);
    UNUSED(trace);

    _state.width = w;
    _state.height = h;

    _state.display = XOpenDisplay(NULL);
    assert(_state.display != NULL);

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

void SRGP_end(void)
{
    XFreeGC(_state.display, _state.gc);
    XDestroyWindow(_state.display, _state.window);
    XCloseDisplay(_state.display);
}

void
SRGP_beep(void)
{
    XBell(_state.display, 0);
}

void
SRGP_setFillStyle(drawStyle value)
{
    XSetFillStyle(_state.display, _state.gc, value);
}

void
SRGP_setFillBitmapPattern(int value)
{
//    XSetStipple(_state.display, _state.gc, 
}

void
SRGP_fillRectangleCoord(int left_x, int bottom_y, int right_x, int top_y)
{
    XFillRectangle(
        _state.display,
        _state.window,
        _state.gc,
        left_x,
        _state.height - top_y,
        right_x - left_x + 1,
        top_y - bottom_y + 1);
}
