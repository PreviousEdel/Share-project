#include <stdio.h>

#define COUNT 100

void main()
{
	double new_x = 0, new_y = 0, prev_x = 0, prev_y = 0;

	for (int i = 0; i < COUNT; i++)
	{
		new_x = prev_y + 1 - 1.4 * prev_x;
		new_y = 0.3 * prev_x;
		prev_x = new_x;
		prev_y = new_y;

		printf("(%.2lf, %.2lf)\n", new_x, new_y);
	}

}