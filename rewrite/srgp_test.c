#include <stdio.h>
#include <unistd.h>

#include "srgp.h"

int main(void)
{
    SRGP_begin("SRGP Patterns", 950, 720, 2, TRUE);
    SRGP_text(SRGP_defPoint(5, 700), "SRGP patterns (drawn in black in REPLACE mode)");
    SRGP_text(SRGP_defPoint(5, 680), "On far right, use of color is shown.");
    SRGP_text(SRGP_defPoint(45, 660), "Hit any key to exit...");

    sleep(3);
    SRGP_end();
}
