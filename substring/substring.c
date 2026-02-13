#include "substring.h"
#include <string.h>

/**
 * is_valid_substring - Checks if substring at start is a valid concatenation
 * @s: The full string
 * @start: Starting index
 * @words: Array of words to match
 * @nb_words: Number of words
 * @word_len: Length of each word
 *
 * Return: 1 if valid, 0 otherwise
 */
static int is_valid_substring(char const *s, int start,
			      char const **words, int nb_words, int word_len)
{
	int *used;
	int i, j;
	int found;

	used = malloc(nb_words * sizeof(int));
	if (!used)
		return (0);

	for (i = 0; i < nb_words; i++)
		used[i] = 0;

	for (i = 0; i < nb_words; i++)
	{
		found = 0;
		for (j = 0; j < nb_words; j++)
		{
			if (!used[j] &&
			    strncmp(s + start + i * word_len, words[j], word_len) == 0)
			{
				used[j] = 1;
				found = 1;
				break;
			}
		}
		if (!found)
		{
			free(used);
			return (0);
		}
	}
	free(used);
	return (1);
}

/**
 * add_index - Adds index to array with capacity growth
 * @indices: Pointer to indices array
 * @count: Current count
 * @capacity: Pointer to current capacity
 * @idx: Index to add
 *
 * Return: Updated indices pointer, or NULL on failure
 */
static int *add_index(int *indices, int count, int *capacity, int idx)
{
	int *tmp;

	if (count >= *capacity)
	{
		*capacity *= 2;
		tmp = realloc(indices, *capacity * sizeof(int));
		if (!tmp)
		{
			free(indices);
			return (NULL);
		}
		indices = tmp;
	}
	indices[count] = idx;
	return (indices);
}

/**
 * scan_string - Scans string for matching substrings
 * @s: The string to scan
 * @words: Array of words
 * @nb_words: Number of words
 * @word_len: Length of each word
 * @total_len: Total substring length
 * @s_len: Length of string s
 * @count: Output - number of matches found
 *
 * Return: Allocated array of indices, or NULL
 */
static int *scan_string(char const *s, char const **words, int nb_words,
			int word_len, int total_len, size_t s_len, int *count)
{
	int i;
	int *indices;
	int capacity;

	capacity = 8;
	indices = malloc(capacity * sizeof(int));
	if (!indices)
		return (NULL);

	*count = 0;
	for (i = 0; i <= (int)s_len - total_len; i++)
	{
		if (is_valid_substring(s, i, words, nb_words, word_len))
		{
			indices = add_index(indices, *count, &capacity, i);
			if (!indices)
				return (NULL);
			(*count)++;
		}
	}
	return (indices);
}

/**
 * find_substring - Finds all substrings that are concatenations of words
 * @s: The string to scan
 * @words: Array of words (all same length)
 * @nb_words: Number of words in array
 * @n: Output - number of indices found
 *
 * Return: Allocated array of starting indices, or NULL
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	size_t s_len;
	int word_len;
	int total_len;
	int *indices;
	int count;

	if (!s || !words || nb_words <= 0 || !n)
		return (NULL);

	s_len = strlen(s);
	word_len = strlen(words[0]);
	total_len = nb_words * word_len;

	if (word_len == 0 || s_len < (size_t)total_len)
	{
		*n = 0;
		return (NULL);
	}

	indices = scan_string(s, words, nb_words, word_len, total_len, s_len, &count);
	if (!indices)
		return (NULL);

	*n = count;
	if (count == 0)
	{
		free(indices);
		return (NULL);
	}

	indices = realloc(indices, count * sizeof(int));
	return (indices);
}
