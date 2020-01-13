#include <stdbool.h>

#define TRUE true
#define FALSE false

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point bottomLeft;
    point topRight;
} rectangle;

point SRGP_defPoint(int x, int y);
void SRGP_text(point origin, char* text);
void SRGP_begin(char* name, int w, int h, int planes, bool trace);
void SRGP_end(void);
void SRGP_beep(void);
