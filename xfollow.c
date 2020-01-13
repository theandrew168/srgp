#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>

int
main(void)
{
    Display* dpy = XOpenDisplay(NULL);
    assert(dpy);

    int screen = XDefaultScreen(dpy);

    int black = XBlackPixel(dpy, screen);
    int white = XWhitePixel(dpy, screen);

    Window w = XCreateSimpleWindow(
        dpy,
        XRootWindow(dpy, screen),
        0,
        0,
        200,
        100,
        0,
        black,
        black);

    XSelectInput(dpy, w, StructureNotifyMask);
    XMapWindow(dpy, w);

    GC gc = XCreateGC(dpy, w, 0, NULL);
    XSetForeground(dpy, gc, white);

    for (;;) {
        XEvent e;
        XNextEvent(dpy, &e);
        if (e.type == MapNotify) {
            break;
        }
    }

    XDrawLine(dpy, w, gc, 10, 60, 180, 20);
    XFlush(dpy);

    sleep(3);

    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, w);
    XCloseDisplay(dpy);
}
