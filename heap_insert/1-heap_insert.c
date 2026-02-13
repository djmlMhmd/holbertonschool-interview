#include "binary_trees.h"

/**
 * heap_size - Counts the number of nodes in a heap
 * @root: Pointer to the root node
 *
 * Return: Number of nodes
 */
static size_t heap_size(heap_t *root)
{
	if (!root)
		return (0);
	return (1 + heap_size(root->left) + heap_size(root->right));
}

/**
 * find_insert_parent - Finds the parent for the next insertion
 * @root: Pointer to the root node
 * @count: Current number of nodes (0-based)
 * @is_right: Output - 1 if new node is right child, 0 if left
 *
 * Return: Parent node, or NULL if new node should be root
 */
static heap_t *find_insert_parent(heap_t *root, size_t count, int *is_right)
{
	size_t k = count + 1;
	size_t mask = 1;
	heap_t *parent = NULL;
	heap_t *current = root;

	if (k == 1)
		return (NULL);

	while (mask * 2 <= k)
		mask *= 2;
	mask >>= 1;

	while (mask > 0)
	{
		parent = current;
		if (k & mask)
			current = current->right;
		else
			current = current->left;
		mask >>= 1;
	}

	*is_right = (k & 1);
	return (parent);
}

/**
 * sift_up - Sifts a node up to restore max heap property
 * @node: Node to sift up
 *
 * Return: Pointer to node containing the inserted value after sift
 */
static heap_t *sift_up(heap_t *node)
{
	heap_t *parent;
	int tmp;

	while (node->parent && node->n > node->parent->n)
	{
		parent = node->parent;
		tmp = node->n;
		node->n = parent->n;
		parent->n = tmp;
		node = parent;
	}
	return (node);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to store in the new node
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *node;
	heap_t *parent;
	size_t count;
	int is_right;

	if (!root)
		return (NULL);

	count = heap_size(*root);
	parent = find_insert_parent(*root, count, &is_right);

	if (!parent)
	{
		node = binary_tree_node(NULL, value);
		if (!node)
			return (NULL);
		*root = node;
		return (node);
	}

	node = binary_tree_node(parent, value);
	if (!node)
		return (NULL);

	if (is_right)
		parent->right = node;
	else
		parent->left = node;

	return (sift_up(node));
}
