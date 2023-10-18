#include "main.h"



/**
 * cm_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int cm_eputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_FLUSH ];

	if (c== BUFFER_FLUSH || i >= WRITE_BUFFER_FLUSH )
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH )
    {
        buffer[i++] = c;
    }
		
	return (1);
}


/**
 * cm_eputs - prints an input string
 * @str: A pointer to a string to be printed
 * 
 * Return: Nothing
 */
void cm_eputs(char *str)
{
    int i;

    if (str == NULL)
    {
        return; /*Handle NULL input*/
    }

    for (i = 0; str[i] != '\0'; i++) {
        cm_putchar(str[i]); /*Call _putchar for each character in the string*/
    }
}

/**
 * cm_putfd - writes a character to given file descriptor(fd)
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */


int cm_putfd(char c , int fd)
{
    static int i;
    static char buffer[WRITE_BUFFER_FLUSH];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_FLUSH)
    {
        write(fd, buffer, i);
        i = 0;
    }

   if (c != BUFFER_FLUSH)
   {
    buffer[i++] = c;
   }
		
	return (1);

}

/**
 * cm_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int cm_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
    {
        		return (0);

    }
	while (*str)
	{
		i += cm_putfd(*str++, fd);
	}
	return (i);
}

