#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * is_palindrome_recursive - checks if two halves of a linked list are equal
 * @left: pointer to the left half of the linked list
 * @right: pointer to the right half of the linked list
 * Return: 1 if equal, 0 otherwise
 */
int is_palindrome_recursive(listint_t **left, listint_t *right)
{
    if (right == NULL)
        return 1;

    if (!is_palindrome_recursive(left, right->next))
        return 0;

    if ((*left)->n != right->n)
        return 0;

    *left = (*left)->next;
    return 1;
}

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: pointer to the head of the linked list
 * Return: 1 if it is a palindrome, 0 otherwise
 */
int is_palindrome(listint_t **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return 1;

    return is_palindrome_recursive(head, *head);
}
