#include "main.h"


/**
 * bfree - Frees a pointer and sets the address to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


/**
 * _memset - Fills memory with a constant byte.
 * @dest: Pointer to the memory area.
 * @value: The byte to fill *dest with.
 * @size: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area dest.
 */
char *cm_memset(char *dest, char value, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++) {
        dest[i] = value;  /* Fill each byte of the memory area with the specified byte */
    }
    return (dest);  /* Return a pointer to the memory area dest */
}


/**
 * ffree - Frees a string of strings.
 * @str_array: String array to be freed.
 */
void ffree(char **str_array)
{
    char **temp_ptr = str_array; 

    if (!str_array) /*Check if the input pointer is NULL*/
        return;

    while (*str_array) /* Iterate through the strings until a NULL pointer is encountered */
        free(*str_array++); /* Free each individual string*/

    free(temp_ptr); /* Free the pointer to the string array */
}

/**
 * _realloc - Reallocates a block of memory.
 * @prev_ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block of memory.
 */
void *_realloc(void *prev_ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    unsigned int i;

    if (!prev_ptr) /* If prev_ptr is NULL, equivalent to malloc */
        return malloc(new_size);

    if (!new_size) /* If new_size is 0, equivalent to free and return NULL */
    { 
        free(prev_ptr);
        return NULL;
    }

    if (new_size == old_size) /* If the sizes are the same, no need to reallocate */
        return prev_ptr;

    new_ptr = malloc(new_size); /* Allocate memory for the new block */
    if (!new_ptr) 
        return NULL;

    /* Copy data from the old block to the new block, limited by the smaller of old_size and new_size */
    for (i = 0; i < old_size && i < new_size; i++) {
        new_ptr[i] = ((char *)prev_ptr)[i];
    }

    free(prev_ptr); 

    return (new_ptr);
}


