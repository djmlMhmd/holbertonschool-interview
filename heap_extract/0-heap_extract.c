#include "binary_trees.h"
#include <stdlib.h>

/**
 * swap_nodes - Swaps the values of two nodes.
 * @a: First node.
 * @b: Second node.
 */
void swap_nodes(heap_t *a, heap_t *b)
{
    int temp = a->n;
    a->n = b->n;
    b->n = temp;
}

/**
 * heapify_down - Restores the Max Heap property by heapifying down.
 * @node: Pointer to the node to start heapifying from.
 */
void heapify_down(heap_t *node)
{
    heap_t *largest = node;
    heap_t *left = node->left;
    heap_t *right = node->right;

    if (left && left->n > largest->n)
        largest = left;
    if (right && right->n > largest->n)
        largest = right;

    if (largest != node)
    {
        swap_nodes(node, largest);
        heapify_down(largest);
    }
}

/**
 * tree_height - Measures the height of a binary tree.
 * @tree: Pointer to the root node of the tree to measure.
 * Return: The height of the tree.
 */
int tree_height(const heap_t *tree)
{
    if (!tree)
        return (0);

    int left_height = tree_height(tree->left);
    int right_height = tree_height(tree->right);

    return ((left_height > right_height ? left_height : right_height) + 1);
}

/**
 * last_node_in_level_order - Find the last node in level-order traversal.
 * @root: Pointer to the root of the tree.
 * Return: Pointer to the last node.
 */
heap_t *last_node_in_level_order(heap_t *root)
{
    if (!root)
        return (NULL);

    heap_t *queue[1024]; /* Static queue to avoid dynamic memory allocation */
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        heap_t *node = queue[front++];

        if (node->left)
            queue[rear++] = node->left;
        if (node->right)
            queue[rear++] = node->right;
    }

    return (queue[front - 1]);
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap.
 * @root: Double pointer to the root node of the heap.
 * Return: The value stored in the root node.
 */
int heap_extract(heap_t **root)
{
    if (!root || !*root)
        return (0);

    heap_t *last_node = last_node_in_level_order(*root);
    int root_value = (*root)->n;

    if (last_node == *root)
    {
        free(*root);
        *root = NULL;
        return (root_value);
    }

    /* Swap the root with the last node */
    swap_nodes(*root, last_node);

    /* Remove the last node */
    if (last_node->parent->left == last_node)
        last_node->parent->left = NULL;
    else
        last_node->parent->right = NULL;

    free(last_node);

    /* Restore Max-Heap property */
    heapify_down(*root);

    return (root_value);
}
