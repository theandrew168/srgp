# SRGP Rewrite Checklist

### attribute.c
- [ ] void SRGP_setAttributes (attributeGroup* group);
- [ ] void SRGP_setBackgroundColor (int colorIndex);
- [ ] void SRGP_setClipRectangle (rectangle clipRect);
- [ ] void SRGP_setColor (int colorIndex);
- [ ] void SRGP_setFillBitmapPattern (int patternIndex);
- [ ] void SRGP_setFillPixmapPattern (int patternIndex);
- [ ] void SRGP_setFillStyle (drawStyle);
- [ ] void SRGP_setFont (int value);
- [ ] void SRGP_setLineStyle (lineStyle);
- [ ] void SRGP_setLineWidth (int width);
- [ ] void SRGP_setMarkerStyle (markerStyle);
- [ ] void SRGP_setMarkerSize (int markerSize);
- [ ] void SRGP_setPenBitmapPattern (int patternIndex);
- [ ] void SRGP_setPenPixmapPattern (int patternIndex);
- [ ] void SRGP_setPenStyle (drawStyle);
- [ ] void SRGP_setPlaneMask (int value);
- [ ] void SRGP_setWriteMode (writeMode);

### canvas.c
- [ ] canvasID SRGP_createCanvas (int width, int height);
- [ ] void SRGP_useCanvas (canvasID id);
- [ ] void SRGP_deleteCanvas (canvasID id);

### color.c
- [ ] void SRGP_loadCommonColor (int entry, char *name);
- [ ] void SRGP_loadColorTable (int start, int cnt, ush *r, ush *g, ush *b);
- [ ] void SRGP_loadSingleColor (int start, ush r, ush g, ush b);

### cursor.c, font.c, pattern.c
- [ ] void SRGP_loadCursor (int index, int CURSOR_SHAPE);
- [ ] void SRGP_loadFont (int font_index, char* filename);
- [ ] void SRGP_inquireTextExtent (char *text, int *width, int *height, int *descent);
- [ ] int SRGP_loadBitmapPatternsFromFile (FILE*);
- [ ] int SRGP_loadPixmapPatternsFromFile (FILE*);
- [ ] void SRGP_loadBitmapPattern (int index, char *data);
- [ ] void SRGP_loadPixmapPattern (int index, int *data);

### input.c
- [ ] void SRGP_setInputMode (inputDevice, inputMode);
- [ ] inputDevice SRGP_waitEvent (int maxWaitTime);
- [ ] void SRGP_getLocator (locatorMeasure* measure);
- [ ] void SRGP_getKeyboard (char *measure, int measureSize);
- [ ] void SRGP_getDeluxeLocator (deluxeLocatorMeasure*);
- [ ] void SRGP_getDeluxeKeyboard (deluxeKeyboardMeasure*);
- [ ] void SRGP_sampleLocator (locatorMeasure*);
- [ ] void SRGP_sampleKeyboard (char *measure, int bufsize);
- [ ] void SRGP_sampleDeluxeLocator (deluxeLocatorMeasure*);
- [ ] void SRGP_sampleDeluxeKeyboard (deluxeKeyboardMeasure*);
- [ ] void SRGP_setLocatorMeasure (point position);
- [ ] void SRGP_setKeyboardMeasure (char*);
- [ ] void SRGP_setLocatorEchoType (echoType);
- [ ] void SRGP_setLocatorEchoCursorShape (int id);
- [ ] void SRGP_setLocatorEchoRubberAnchor (point position);
- [ ] void SRGP_setLocatorButtonMask (int activeButtons);
- [ ] void SRGP_setKeyboardProcessingMode (keyboardMode);
- [ ] void SRGP_setKeyboardEchoColor (int value);
- [ ] void SRGP_setKeyboardEchoOrigin (point origin);
- [ ] void SRGP_setKeyboardEchoFont (int fontindex);

### inquire.c
void SRGP_inquireAttributes (attributeGroup *group);
rectangle SRGP_inquireClipRectangle (void);
canvasID SRGP_inquireActiveCanvas (void);
rectangle SRGP_inquireCanvasExtent (canvasID id);
void SRGP_inquireCanvasSize (canvasID, int *w, int *h);
int	SRGP_inquireCanvasDepth (void);
lineStyle SRGP_inquireLineStyle (void);
void SRGP_inquireColorTable (int start, int cnt, ush *r, ush *g, ush *b);

### output.c
- [ ] point SRGP_defPoint (int x, int y);
- [ ] rectangle SRGP_defRectangle (int leftX, int bottomY, int rightX, int topY);
- [ ] void SRGP_beep (void);
- [ ] void SRGP_pointCoord (int x, int y);
- [ ] void SRGP_point (point);
- [ ] void SRGP_polyPoint (int vertexCount, point *vertices);
- [ ] void SRGP_polyPointCoord (int vertexCount, int *xArray, int *yArray);
- [ ] void SRGP_markerCoord (int x, int y);
- [ ] void SRGP_marker (point pt);
- [ ] void SRGP_polyMarker (int vertexCount, point *vertices);
- [ ] void SRGP_polyMarkerCoord (int vertexCount, int *xArray, int *yArray);
- [ ] void SRGP_lineCoord (int x1, int y1, int x2, int y2);
- [ ] void SRGP_line (point pt1, point pt2);
- [ ] void SRGP_rectangleCoord (int leftX, int bottomY, int rightX, int topY);
- [ ] void SRGP_rectanglePt (point bottomLeft, point topRight);
- [ ] void SRGP_rectangle (rectangle rect);
- [ ] void SRGP_polyLine (int vertexCount, point *vertices);
- [ ] void SRGP_polyLineCoord (int vertexCount, int *xArray, int *yArray);
- [ ] void SRGP_polygon (int vertexCount, point *vertices);
- [ ] void SRGP_polygonCoord (int vertexCount, int *xArray, int *yArray);
- [ ] void SRGP_fillRectangleCoord (int leftX, int bottomY, int rightX, int topY);
- [ ] void SRGP_fillRectanglePt (point bottomLeft, point topRight);
- [ ] void SRGP_fillRectangle (rectangle);
- [ ] void SRGP_fillPolygon (int vertexCount, point *vertices);
- [ ] void SRGP_fillPolygonCoord (int vertexCount, int *xArray, int *yArray);
- [ ] void SRGP_ellipse (rectangle);
- [ ] void SRGP_ellipseArc (rectangle extentRect, double startAngle, double endAngle);
- [ ] void SRGP_fillEllipse (rectangle);
- [ ] void SRGP_fillEllipseArc (rectangle, double a1, double a2);
- [ ] void SRGP_text (point origin, char *text);
- [ ] void SRGP_refresh (void);

### raster.c
- [ ] void SRGP_copyPixel (canvasID sourceCanvas, rectangle sourceRect, point destCorner);

### state.c
- [ ] void SRGP_begin (char *name, int w, int h, int planes, boolean trace);
- [ ] void SRGP_beginWithDebug (char *name, int w, int h, int planes, boolean trace);
- [ ] void SRGP_disableDebugAids (void);
- [ ] void SRGP_enableBlockedWait (void);
- [ ] void SRGP_setErrorHandlingMode (errorHandlingMode);
- [ ] void SRGP_enableSynchronous (void);
- [ ] void SRGP_tracing (boolean);
- [ ] void SRGP_allowResize (boolean);
- [ ] void SRGP_registerResizeCallback (funcptr);
- [ ] void SRGP_changeScreenCanvasSize (int newwidth, int newheight);
- [ ] void SRGP_end (void);
