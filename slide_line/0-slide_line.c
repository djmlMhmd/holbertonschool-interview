#include "slide_line.h"
#include <sys/types.h>

/**
 * slide_left - slides and merges the array to the left
 * @line: pointer to array
 * @size: size of array
 */
void slide_left(int *line, size_t size)
{
    size_t i, pos = 0;
    int prev = 0;

    for (i = 0; i < size; i++)
    {
        if (line[i] == 0)
            continue;
        if (prev == 0)
        {
            prev = line[i];
        }
        else if (prev == line[i])
        {
            line[pos++] = prev * 2;
            prev = 0;
        }
        else
        {
            line[pos++] = prev;
            prev = line[i];
        }
    }
    if (prev != 0)
        line[pos++] = prev;
    while (pos < size)
        line[pos++] = 0;
}

/**
 * slide_right - slides and merges the array to the right
 * @line: pointer to array
 * @size: size of array
 */
void slide_right(int *line, size_t size)
{
    ssize_t i, pos = size - 1;
    int prev = 0;

    for (i = size - 1; i >= 0; i--)
    {
        if (line[i] == 0)
            continue;
        if (prev == 0)
        {
            prev = line[i];
        }
        else if (prev == line[i])
        {
            line[pos--] = prev * 2;
            prev = 0;
        }
        else
        {
            line[pos--] = prev;
            prev = line[i];
        }
    }
    if (prev != 0)
        line[pos--] = prev;
    while (pos >= 0)
        line[pos--] = 0;
}

/**
 * slide_line - slides and merges an array of integers like 2048
 * @line: pointer to array
 * @size: number of elements
 * @direction: SLIDE_LEFT or SLIDE_RIGHT
 * Return: 1 on success, 0 on failure
 */
int slide_line(int *line, size_t size, int direction)
{
    if (!line || (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
        return (0);

    if (direction == SLIDE_LEFT)
        slide_left(line, size);
    else
        slide_right(line, size);

    return (1);
}
