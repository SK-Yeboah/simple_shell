#include "main.h"

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buffer: Address of the string to modify.
 *
 * Return: Always 0.
 */

void remove_comments(char *buffer)
{
    int i = 0;

    /*Iterate through the string until a null terminator is encountered*/
    while (buffer[i] != '\0') {
        /*Check for '#' preceded by a space or at the beginning of the string*/
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' ')) {
            buffer[i] = '\0'; /* Replace '#' with '\0'*/
            break;
        }
        i++;
    }
}



/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int cm_putchar(char c)
{
    static int i;
    static char buffer[WRITE_BUFFER_FLUSH];

    /* If the buffer is full or BUF_FLUSH is encountered, flush the buffer*/   if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_FLUSH)
   if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_FLUSH)
    {
        write(1, buffer, i);
        i = 0;
    }

    /* Add the character to the buffer (except BUF_FLUSH)*/
    if (c != BUFFER_FLUSH)
        buffer[i++] = c;

    return (1);
}

