/* toview.c -- toview(d2point) to translate the d2point from window coordination into viewport coordination;
 */
#include "all.h"
struct d2point toview(struct d2point winpoint)
{
	float VXR,VXL,VYT,VYB,WXR,WXL,WYB,WYT;
	float a,b,c,d;
	float Xw,Yw,Xs,Ys;
	struct d2point viewpoint;	

	Xw=winpoint.x;
	Yw=winpoint.y;
		
	WXL=winlt.x;
	WXR=winrb.x;
	WYT=winlt.y;
	WYB=winrb.y;	
	VXL=viewlt.x;
	VXR=viewrb.x;
	VYT=viewlt.y;
	VYB=viewrb.y;

	a=(VXR-VXL)/(WXR-WXL);
	b=VXL-WXL*(VXR-VXL)/(WXR-WXL);
	c=(VYT-VYB)/(WYT-WYB);
	d=VYB-WYB*(VYT-VYB)/(WYT-WYB);
	
	Xs=a*Xw+b;
	Ys=c*Yw+d;

	viewpoint.x=Xs;
	viewpoint.y=Ys;
	
	return(viewpoint);
}
