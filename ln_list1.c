#include "main.h"


/**
 * add_node - adds node to the begining of the linkded list 
 * @head: double pointer to the linkedlist_node list
 * @string: new string to add in the node
 * @number: node index used by history
 * 
 * Return:  The address of the new  element, or NULL if it fails
 * 
*/

linkedList_node *add_node_beg(linkedList_node **head, const char *string, int number)
{
    linkedList_node *new_node;

    if(!head)
    {
        return (NULL);
    }

    new_node = malloc(sizeof(linkedList_node));


    if(!new_node)
    {
        return (NULL);
    }

    cm_memset((void *)new_node, 0, sizeof(linkedList_node));
    new_node->number = number;
    
    if(string)
    {
        new_node->string = cm_strdup(string);
        if(!new_node->string)
        {
            free(new_node);
            return (NULL);
        }
    }

    new_node->next =*head;
    *head = new_node;
    return (new_node);
}


/**
 * add_node_end - Adds node to the end of the linked list
 * @head: Double pointer to head node
 * @string: string to add to the node
 * 
 * Return: the address of the new element or NULL field if it failed
 * 
*/

linkedList_node *add_node_end(linkedList_node **head, const char *string, int num)
{
    linkedList_node *new_node, *node;

    if (!head)
    {
        return (NULL);
    }

    node = *head;
    new_node = malloc(sizeof(linkedList_node));

    if(!new_node)
    {
        return (NULL);
    }

    cm_memset((void *)new_node, 0, sizeof(linkedList_node));
    new_node->number = num;

    if (string)
    {
        new_node->string = cm_strdup(string);
        if(!new_node->string)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
        {
            node=node->next;
        }
        node->next=new_node;
    }
    else
    {
        *head = new_node;
    }
    return (new_node);

}

/**
 * delete_nodeint_at_index - deletes a node in a linked list at a certain index
 * @head: pointer to the first element in the list
 * @index: index of the node to delete
 *
 * Return: 1 (Success), or -1 (Fail)
 */
int delete_nodeint_at_index(linkedList_node **head, unsigned int index)
{
	linkedList_node *temp = *head;
	linkedList_node *current = NULL;
	unsigned int i = 0;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		*head = (*head)->next;
		free(temp);
		return (1);
	}

	while (i < index - 1)
	{
		if (!temp || !(temp->next))
			return (-1);
		temp = temp->next;
		i++;
	}


	current = temp->next;
	temp->next = current->next;
	free(current);

	return (1);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: Pointer to first node
 *
 * Return: Array of strings
 */
char **list_to_strings(linkedList_node *head)
{
	linkedList_node *node = head;
	size_t i = get_list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
    {
        return (NULL);
    }
		
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
    {
        return (NULL);
    }
		
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(cm_strlen(node->string) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
            {
                free(strs[j]);
            }	
			free(strs);
			return (NULL);
		}

		str = cm_strcpy(str, node->string);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}




/**
 * get_node_index - gets the index of a node
 * @head: A Pointer to list head
 * @node: A Pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(linkedList_node *head, linkedList_node *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
        {
            return (i);
        }
			
		head = head->next;
		i++;
	}
	return (-1);
}

