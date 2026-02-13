#include "sort.h"

/**
 * print_subarray - Prints a subarray with comma separation
 * @array: The array to print
 * @size: Number of elements
 */
static void print_subarray(const int *array, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		printf("%s%d", i > 0 ? ", " : "", array[i]);
	printf("\n");
}

/**
 * merge - Merges two sorted subarrays
 * @array: The array containing both subarrays
 * @left_size: Size of left subarray
 * @right_size: Size of right subarray
 * @tmp: Temporary buffer for merging
 */
static void merge(int *array, size_t left_size, size_t right_size, int *tmp)
{
	size_t i, j, k;
	size_t total = left_size + right_size;

	for (i = 0; i < total; i++)
		tmp[i] = array[i];

	i = 0;
	j = left_size;
	k = 0;

	while (i < left_size && j < total)
	{
		if (tmp[i] <= tmp[j])
			array[k++] = tmp[i++];
		else
			array[k++] = tmp[j++];
	}
	while (i < left_size)
		array[k++] = tmp[i++];
	while (j < total)
		array[k++] = tmp[j++];
}

/**
 * merge_sort_rec - Recursive merge sort
 * @array: The array to sort
 * @size: Number of elements
 * @tmp: Temporary buffer (single allocation for entire sort)
 */
static void merge_sort_rec(int *array, size_t size, int *tmp)
{
	size_t left_size, right_size;

	if (size <= 1)
		return;

	left_size = size / 2;
	right_size = size - left_size;

	merge_sort_rec(array, left_size, tmp);
	merge_sort_rec(array + left_size, right_size, tmp);

	printf("Merging...\n");
	printf("[left]: ");
	print_subarray(array, left_size);
	printf("[right]: ");
	print_subarray(array + left_size, right_size);

	merge(array, left_size, right_size, tmp);

	printf("[Done]: ");
	print_subarray(array, size);
}

/**
 * merge_sort - Sorts an array of integers in ascending order using Merge Sort
 * @array: The array to sort
 * @size: Number of elements in the array
 */
void merge_sort(int *array, size_t size)
{
	int *tmp;

	if (!array || size < 2)
		return;

	tmp = malloc(size * sizeof(int));
	if (!tmp)
		return;

	merge_sort_rec(array, size, tmp);

	free(tmp);
}
