#include <stdio.h>
#include <math.h>
#include "menger.h"

/**
 * is_sponge_filled - Determines if a position is filled in Menger Sponge
 * @level: Current level of the Menger Sponge
 * @row: Current row position
 * @col: Current column position
 *
 * Return: 1 if the position is filled, 0 otherwise
 */
int is_sponge_filled(int level, int row, int col)
{
	/* Iterate through levels */
	for (; level > 0; level--)
	{
		/* If we're in the center square of the current 3x3 grid, it's not filled */
		if ((row % 3 == 1) && (col % 3 == 1))
			return (0);

		/* Reduce row and column to local coordinates within the subgrid */
		row /= 3;
		col /= 3;
	}

	/* At level 0, always filled */
	return (1);
}

/**
 * menger - Draws a 2D Menger Sponge of given level
 * @level: Level of the Menger Sponge to draw
 */
void menger(int level)
{
	int size, row, col;

	/* Do nothing if level is negative */
	if (level < 0)
		return;

	/* Calculate the size of the sponge (3^level) */
	size = pow(3, level);

	/* Draw the sponge */
	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			/* Print '#' if the position is filled, ' ' otherwise */
			printf("%c", is_sponge_filled(level, row, col) ? '#' : ' ');
		}
		printf("\n");
	}
}
