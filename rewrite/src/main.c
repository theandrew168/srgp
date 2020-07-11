#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "srgp.h"

int
main(void)
{
    SRGP_begin("SRGP Rewrite", 800, 600, 2, FALSE);

    SRGP_lineCoord(175, 200, 320, 200);
    SRGP_lineCoord(200, 140, 200, 280);

    int months[] = { 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320 };
    int balance[] = { 160, 180, 260, 210, 200, 240, 250, 170, 180, 170, 220, 190 };
    SRGP_polyLineCoord(12, months, balance);

    point bowtie[] = {
        { 100, 100 },
        { 100, 60 },
        { 120, 76 },
        { 140, 60 },
        { 140, 100 },
        { 120, 84 },
        { 100, 100 },
    };
    SRGP_polyLine(7, bowtie);

    SRGP_polyMarkerCoord(12, months, balance);

    SRGP_rectangleCoord(50, 25, 150, 175);

    rectangle r = SRGP_defRectangle(50 + 5, 25 + 5, 150 + 5, 175 + 5);
    SRGP_rectangle(r);

    nanosleep(&(struct timespec){ .tv_sec = 3}, NULL);
    SRGP_end();
}
