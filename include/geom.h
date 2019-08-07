/**   G E O M E T R I C    A R I T H M E T I C    **/

/* Adds two points, returning the result */
point GEOM_sumOfPoints (point pt1, point pt2);

/* Computes one of the dimensions of a given rectangle */
int GEOM_widthOfRect (rectangle r);
int GEOM_heightOfRect (rectangle r);

/* Computes rectangle result of binary operation on two rects */
void GEOM_computeRectUnion (rectangle r1, rectangle r2, 
			    rectangle *result);
int  GEOM_computeRectIntersection (rectangle r1, rectangle r2, 
				   rectangle *result);
        /* RETURNS BOOLEAN: is there a non-null intersection? */

/* Returns the rectangle whose center is the same as the center of
 * the given rectangle R and whose dimensions are as given.
 */
rectangle GEOM_rectWithCommonCenter 
   (rectangle r, int width, int height);

/* Returns the rectangle one of whose diagonals is specified by the
 * two given points.  Rectangles are defined by the SW-NE diagonal.
 * This procedure is useful when the caller "has" a diagonal but
 * knows not which it is.
 */
rectangle GEOM_rectFromDiagPoints (point pt1, point pt2);

/* Returns TRUE if and only if the given point is on the boundary of
 * or in the interior of the given rectangle.
 */
int GEOM_ptInRect (point pt, rectangle rect);
