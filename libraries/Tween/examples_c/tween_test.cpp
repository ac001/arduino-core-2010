// gcc -Wall -o tween_chase tween_chase.c
#include <stdio.h>
#include "Tween.h"

int main(int argc, char **argv)
{
	int t;
	int i;
	int num_chases = 3;
	Tween_t chase[3];
	float res;
	float targets[3] ={1,0,1};
	
	for (i=0;i<num_chases;i++)
	{
		 Tween_init(&chase[i]);
		 Tween_setType(&chase[i], (i<1)?0:1);
		 Tween_line(&chase[i],targets[i],100);
	}
	// print 100 interpolated values
	for (t=0; t <= 100;t++)
	{
		printf("\n(t:%d) ",(int)t);
		for (i=0;i<num_chases;i++)
		{
			// half way
			if (t == 50)
			{
				Tween_line(&chase[0], 0.4, 0); // STOP
				Tween_line(&chase[1],0.25,100);
			}
			// Tween_tick() should be renamed
			res = Tween_tick(&chase[i],(float) t);
			printf(" %d ",(int) (res*255.0));
		}
	}
	printf("\n");
	return 0;
}
