/* 
 * Rudy Martinez
*/

#include "fonts.h"

void rudyCredits(Rect* r)
{
	rect r;
	r.bot = y;
	r.left = x;
	ggprint8b(r, 16, 0x00ffff00, "Rudy Martinez");
}

