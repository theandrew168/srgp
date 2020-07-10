#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "srgp.h"

int
main(void)
{
    SRGP_begin("SRGP Rewrite", 800, 600, 2, FALSE);

    SRGP_lineCoord(0, 0, 100, 300);

    point a = { 0, 300 };
    point b = { 100, 0 };
    SRGP_line(a, b);

    int xArray[] = { 100, 200 };
    int yArray[] = { 0, 300 };
    SRGP_polyLineCoord(2, xArray, yArray);

    point ab[] = {
        { 100, 300 },
        { 200, 0 },
    };
    SRGP_polyLine(2, ab);

    nanosleep(&(struct timespec){ .tv_sec = 3}, NULL);
    SRGP_end();
}
