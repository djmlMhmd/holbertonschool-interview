#include <stdio.h>
#include "sandpiles.h"

/**
 * print_grid - Print a 3x3 grid
 * @grid: 3x3 grid
 */
static void print_grid(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j)
                printf(" ");
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * is_unstable - Check if the sandpile is unstable
 * @grid: 3x3 grid
 * Return: 1 if unstable, 0 otherwise
 */
static int is_unstable(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (grid[i][j] > 3)
                return (1);
        }
    }
    return (0);
}

/**
 * sandpiles_sum - Computes the sum of two sandpiles
 * @grid1: First sandpile (updated with result)
 * @grid2: Second sandpile
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
    int i, j;
    int tmp[3][3];

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            grid1[i][j] += grid2[i][j];
    }

    while (is_unstable(grid1))
    {
        printf("=\n");
        print_grid(grid1);

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
                tmp[i][j] = 0;
        }

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (grid1[i][j] > 3)
                {
                    tmp[i][j] -= 4;
                    if (i > 0)
                        tmp[i - 1][j] += 1;
                    if (i < 2)
                        tmp[i + 1][j] += 1;
                    if (j > 0)
                        tmp[i][j - 1] += 1;
                    if (j < 2)
                        tmp[i][j + 1] += 1;
                }
            }
        }

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
                grid1[i][j] += tmp[i][j];
        }
    }
}
