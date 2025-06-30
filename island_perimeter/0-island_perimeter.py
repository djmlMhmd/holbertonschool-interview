#!/usr/bin/python3
"""
Module that provides island_perimeter function.
"""


def island_perimeter(grid):
    """
    Returns the perimeter of the island described in grid.

    :param grid: List of list of integers (0 = water, 1 = land)
    :return: Perimeter of the island
    """
    if not grid or not isinstance(grid, list):
        return 0

    perimeter = 0
    rows = len(grid)
    cols = len(grid[0])

    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == 1:
                perimeter += 4
                # check above
                if i > 0 and grid[i - 1][j] == 1:
                    perimeter -= 2
                # check left
                if j > 0 and grid[i][j - 1] == 1:
                    perimeter -= 2
    return perimeter
