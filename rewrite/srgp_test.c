#include <stdio.h>
#include <unistd.h>

#include "srgp.h"

#define CHIP_NAME_BUF_SIZE 10
#define CHIP_WIDTH 40
#define CHIP_HEIGHT 40
#define VERTICAL_MARGIN 40
#define HORIZONTAL_MARGIN 40

int main(void)
{
    SRGP_begin("SRGP Patterns", 950, 720, 2, FALSE);
    SRGP_text(SRGP_defPoint(5, 700), "SRGP patterns (drawn in black in REPLACE mode)");
    SRGP_text(SRGP_defPoint(5, 680), "On far right, use of color is shown.");
    SRGP_text(SRGP_defPoint(45, 660), "Hit any key to exit...");

    SRGP_setFillStyle(BITMAP_PATTERN_OPAQUE);

    int x = 5;
    int y = 5;

    char str[CHIP_NAME_BUF_SIZE] = { 0 };
    for (int i = 0; i < 104; i++) {
        snprintf(str, CHIP_NAME_BUF_SIZE, "%2d", i);

        SRGP_setFillBitmapPattern(i);
        SRGP_fillRectangleCoord(x, y, x + CHIP_WIDTH, y + CHIP_HEIGHT);
        SRGP_text(SRGP_defPoint(x + CHIP_WIDTH + 4, y + 8), str);
        y = y + CHIP_HEIGHT + VERTICAL_MARGIN;

        if (y > 600) {
            y = 5;
            x = x + CHIP_WIDTH + HORIZONTAL_MARGIN;
        }
    }

    sleep(3);
    SRGP_end();
}
