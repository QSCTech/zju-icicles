/* draw.c -- translate the line of the graphics, first to translate the points
 *		to the cast plane and then translate them to the viewport
 *		and then the lines can be drawn.
 */
#include "all.h"

void translate()
{
	struct listnode *ltp;

	ltp=listhead;
	while (ltp!=NULL)
	{
		/* ltp->line1 is the original line */
		/* translate the line into line2 */
		ltp->line2.p1=plane_cast(ltp->line1.p1);
		ltp->line2.p2=plane_cast(ltp->line1.p2);
		
		ltp->line2.p1=toview(ltp->line2.p1);
		ltp->line2.p2=toview(ltp->line2.p2);
		
		ltp=ltp->next;
	}
}
