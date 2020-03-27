/* readline.c -- readline() to read the line point data in file and 
 * 		construct the linklist;
 */

#include "all.h" 

void readline()
{
	FILE	*file;
	int	number=0;
	float	fTemp;
	struct	listnode * node;
	int	state;

	file=fopen("cube.line","rt");
	if (file==NULL)
	{
		printf("can't open file");
		exit(-1);
	}
	while (!feof(file))
	{
		node=(struct listnode *)malloc(sizeof(float)*10+sizeof(int)+sizeof(int *));
		/* each time, read two sets of x, y, z. */	
		fscanf(file,"%f",&fTemp);
		node->line1.p1.x=fTemp;
		
		fscanf(file,"%f",&fTemp);
		node->line1.p1.y=fTemp;

		fscanf(file,"%f",&fTemp);
		node->line1.p1.z=fTemp;

		fscanf(file,"%f",&fTemp);
		node->line1.p2.x=fTemp;

		fscanf(file,"%f",&fTemp);
		node->line1.p2.y=fTemp;

		state=fscanf(file,"%f",&fTemp);
		node->line1.p2.z=fTemp;
	
/*		should consider problem here, but until
		find the reason after debugging. */

		if(state!=-1) {
			node->next=listhead;
			listhead=node;
			number++;
		} else {
/*		not good enough to use 'state' here, no returned value either. */
			free(node);
		}
	}

}
