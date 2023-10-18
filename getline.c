#include "main.h"

/**
 * sigintHandler - Signal handler for handling SIGINT (Ctrl-C).
 * @sig_num: The signal number (unused, indicated by __attribute__((unused))).
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    cm_puts("\n");   /*Print a newline to move to a new line */
    cm_puts("$ ");   /* Print the shell prompt */
    cm_putchar(BUFFER_FLUSH);  /* Flush the character buffer */
}


/**
 * read_buffer - Reads data into a buffer.
 * @info: Parameter struct containing file descriptor and other information.
 * @buffer: Buffer to store the read data.
 * @i: Pointer to the size of data read.
 *
 * Return: Number of bytes read (positive integer) if successful,
 *         0 if the buffer is already filled,
 *         -1 on error (with errno set appropriately).
 */

ssize_t read_buffer(shell_info *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    /* If the buffer is already filled, return 0 (indicating no additional read is needed) */
    if (*i)
    {
         return (0);
    }
       

    /* Read data into the buffer using the specified file descriptor and buffer size */
    r = read(info->readfd, buf, READ_BUFFER_SIZE);
    
    /* Update the size of data read through the pointer i */
    if (r >= 0)
    {
        *i = r;
    }
        

    return (r); /* Return the number of bytes read (or -1 on error) */
}


/**
 * get_input - Gets a line minus the newline.
 * @info: Parameter struct containing information.
 *
 * Return: Bytes read.
 */
ssize_t get_input(shell_info *info)
{
    /* Iterators and buffer length */
    static size_t i, j, len;

    /* Buffer for storing input line */
    static char *buffer; 

   /* Number of bytes read */
    ssize_t r = 0; 
    
    /* Pointers for buffer management */
    char **buf_p = &(info->arg), *p; 

    /* Flush the character buffer */
    cm_putchar(BUFFER_FLUSH); 

    /* Read input into the buffer */
    r = input_buf(info, &buffer, &len); 

    /* EOF encountered */
    if (r == -1)
    {
        return (-1);
    }
        
/* Check if there are commands left in the chain buffer */
    if (len) 
    {
        /* Initialize a new iterator to the current buffer position */
        j = i;
        /* Get a pointer for return */
        p = buffer + i; 
        /* Check for command chains */
        check_chain(info, buffer, &j, i, len);

        /* Iterate to semicolon or end of buffer */
        while (j < len) 
        {
            if (is_chain(info, buffer, &j))
                break; /* If semicolon found, break the loop */
            j++;
        }
        /* Increment past the nulled semicolon */
        i = j + 1;

        /* Reached the end of the buffer */
        if (i >= len) 
        { 
            /* Reset position and length */
            i = len = 0;

            /* Reset command buffer type */
            info->command_BufferType = COMMAND_NORM; 
        }
         /* Pass back the pointer to the current command position */
        *buf_p = p;
        /* Return the length of the current command */
        return (cm_strlen(p)); 
    }
    /* If not a chain, pass back the buffer from _getline() */
    *buf_p = buffer; 

/* Return the length of the buffer from _getline() */
    return (r); 
}



/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct containing information.
 * @buf: Address of the buffer pointer.
 * @len: Address of the length variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(shell_info *info, char **buffer, size_t *length)
{
        ssize_t read = 0;
        size_t len_p = 0;

        /* If nothing left in the buffer, fill it */
        if (!*length) 
        {
            /* Free the previous buffer */
            free(*buffer);
             /* Reset the buffer pointer */
            *buffer = NULL;
            
             /* Register the signal handler for SIGINT */
            signal(SIGINT, sigintHandler);
    #if USE_GETLINE
            /* Use getline to read input into the buffer */
            read = getline(buffer, &len_p, stdin); 
    #else
            read = _getline(info, buffer, &len_p); /* Call the custom _getline function if not using getline */
    #endif
            if (read > 0)
            {
                if ((*buffer)[read - 1] == '\n')
                {
                    /* Remove trailing newline */
                    (*buffer)[read - 1] = '\0'; 
                    read--;
                }
                /* Set the line count flag */
                info->linecount_flag = 1;

                /* Remove comments from the input line */
                remove_comments(*buffer);

                /* Build history list with the input line */
                build_history_list(info, *buffer, info->history_count++);
                 /* Update the length variable */
                *length = read;
                /* Store the buffer pointer in the command buffer */
                info->command_Buffer = buffer; 
            }
        }
        /* Return the number of bytes read */
        return (read); 
}


/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(shell_info *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	read = read_buffer(info, buf, &len);
	if (read == -1 || (read == 0 && len == 0))
    {
        return (-1);

    }

	c = cm_strchr(buf + i, '\n');

        if (c != NULL)
        {
        k = 1 + (unsigned int)(c - buf);  /* Calculate the number of characters until the newline */
        } else
        {
            k = len;  /* If there is no newline, consider the entire remaining buffer length */
        }

        new_p = _realloc(p, s, s ? s + k : k + 1);

        /* MALLOC FAILURE! */
        if (!new_p)
        {
            if (p)
            {
                free(p); 
            }
            return (-1); 
        }

        if (s)
        {
           cm_strncat(new_p, buf + i, k - i);

        }
        else
        {
            cm_strncpy(new_p, buf + i, k - i + 1);

        }

        s += k - i;
        i = k;
        p = new_p;

        if (length)
        {
            *length = s;
        }
            
        *ptr = p;
        return (s);
}

