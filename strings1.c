#include "main.h"


/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
    for (; *needle != '\0'; needle++, haystack++)
    {
        if (*needle != *haystack)
        {
            return NULL;
        }
    }
    return (char *)haystack;  
}



/**
 * cm_strlen - returns the length of a string
 * @s: string to evaluate
 *
 * Return: the length of the string
 */
int cm_strlen(char *s)
{
	int i;

	i = 0;

	while (s[i] != '\0')
	{
		i++;
	}

	return (i);
}

/**
 * *cm_strcpy - copies the string pointed to by src to dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 *
 * Return: the pointer to dest
 */

char *cm_strcpy(char *dest, const char *src)
{
    int i;

    if (dest == NULL || src == NULL)
    {
        return (dest);
    }

    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return (dest);
}


/**
 * cm_strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *cm_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
    {
        return (NULL);
    }
		
	while (*str++)
    {
        length++;
    }
		
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
    {
        return (NULL);
    }
		
	for (length++; length--;)
    {
        ret[length] = *--str;
    }
		
	return (ret);
}


/**
 * _strcat - concatenates two strings
 * @dest: A pointer to the destination buffer
 * @src: A pointer to the source buffer
 *
 * Return: pointer to destination buffer
 */
char *cm_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
    {
        dest++;
    }
	while (*src)
    {
        *dest++ = *src++;
    }
	*dest = *src;
	return (ret);
}


