#include "main.h"

/**
 * get_list_len - Gets the length of a linked list
 * @head: A pointer to the first node
*/
size_t get_list_len(linkedList_node *head)
{
	size_t  length = 0;
	linkedList_node *current = head;

	while (current != 0)
	{
		length++;
		current = current->next;
	}

	return (length);
}

/**
 * print_lnlist_string - prints only string elements of a linked_list 
 * @head: Pointer to the 1st node
 * 
 * Return:the number of nodes 
*/
size_t print_lnlist_string(const linkedList_node *head)
{
	size_t nodeCount = 0;
	
	while (head)
	{
		if (head->string != NULL)
		{
			cm_puts(head->string);
		} else
		{
			cm_puts("(nil)");
		}
		cm_puts("\n");
        head = head->next;
        nodeCount++;
	}
    return (nodeCount);
}

/**
 * free_lnkedlist - Free all nodes in linkdedlist
 * @head_ptr: Address to the pointer to head node
 * 
 * Return:void
*/
void free_lnkedlist(linkedList_node **head_ptr)
{
    linkedList_node *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
    {
        return;
    }

    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->string);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}


/**
 * print_lnlist- prints all elements of a linked_list 
 * @head: Pointer to the 1st node
 * 
 * Return: the number of nodes 
*/

size_t print_lnkdlist(const linkedList_node *head)
{
    size_t i = 0;

    while (head)
    {
        cm_puts(convert_number(head ->number, 10, 0));
		cm_putchar(':');
		cm_putchar(' ');
        if (head->string != NULL)
        {
            cm_puts(head->string);
        } else
        {
            cm_puts("(nil)");
        }
        cm_puts("\n");
        head = head->next;
        i++;
    }
    return (i);
}


/**
 * ln_startsWith - Returns a node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

linkedList_node *ln_startsWith(linkedList_node *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->string, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
        {
            return (node);
        }
		node = node->next;
	}
	return (NULL);
}


