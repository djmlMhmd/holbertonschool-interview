#include "sort.h"

/**
 * print_array - Prints an array of integers
 * @array: The array to print
 * @size: Number of elements in @array
 */
void print_array(const int *array, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		printf("%s%d", i > 0 ? ", " : "", array[i]);
	printf("\n");
}
