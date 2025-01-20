/* cast.c -- plane_cast(struct d3point) to translate the point's coordination 
 *	from the user's coordination to the observation space cast plane.	
 */
 
#include "all.h"

struct d2point plane_cast(struct d3point user3d)
{
	/* user3d : a point in the user's space  */
	/* return the point's cooridation in observation space.*/
	struct d3point obv_point;
	struct d2point cast_point;
	float Xw,Yw,Zw;
	float u,v,a,b,c;
	
	a=viewpoint.x;
	b=viewpoint.y;
	c=viewpoint.z;

	u=(float)(sqrt(a*a+b*b+c*c));
	v=(float)(sqrt(a*a+b*b));
	
	Xw=user3d.x;
	Yw=user3d.y;
	Zw=user3d.z;

	obv_point.x=-1*b/v*Xw+a/v*Yw;
	obv_point.y=-1*a*c/u/v*Xw-b*c/u/v*Yw+v/u*Zw;
	obv_point.z=-1*a/u*Xw-b/u*Yw-c/u*Zw+u;
	
	cast_point.x=obv_point.x*distance/obv_point.z;
	cast_point.y=obv_point.y*distance/obv_point.z;

	return(cast_point);
}
