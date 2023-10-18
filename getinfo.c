#include "main.h"


/**
 * free_info - Frees fields of an info_t struct.
 * @info: Pointer to the info_t struct.
 * @free_all: Flag indicating whether to free all fields (1 for true, 0 for false).
 */
void free_info(shell_info *info, int free_all)
{
    ffree(info->argv); 
    info->argv = NULL;
    info->path = NULL; 

    if (free_all)
    {
        /* If command_buffer is NULL, free the command field */
        if (!info->command_Buffer)
        {
            free(info->arg); 
        }
         /* f environment is not NULL, free the environment list*/
        if (info->env)
        {
            free_lnkedlist(&(info->env));
        }
         /* If history is not NULL, free the history list */
        if (info->history)
        {
            free_lnkedlist(&(info->history));
        }
           /* If aliases is not NULL, free the aliases list */  
        if (info->aliases)
        {
            free_lnkedlist(&(info->aliases)); 
        }
           
        ffree(info->environ); 
        info->environ = NULL;

        /* Free the command_buffer field and set it to NULL */
        bfree((void **)info->command_Buffer);

         /* Close the input file descriptor if greater than 2 */
        if (info->readfd > 2)
        {
            close(info->readfd);
        }
          /*Flush the output buffer*/  
        cm_putchar(BUFFER_FLUSH); 
    }
}

/**
 * clear_info - Initializes fields of an info_t struct.
 * @info: Pointer to the info_t struct.
 */
void clear_info(shell_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


/**
 * set_info - Initializes fields of an info_t struct based on argument vector.
 * @info: Pointer to the info_t struct.
 * @arg_vector: Argument vector (av).
 */
void set_info(shell_info *info, char **arg_vector)
{
    int i = 0;

    /* Set the executable name from the first element of the argument vector */
    info->fname = arg_vector[0];

    /* Check if arguments are provided */
    if (info->arg)
    {
        /* Tokenize arguments and set the argv field */
        info->argv = strtow(info->arg, " \t");
        
        /* If tokenization fails, create a single-element argv */
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = cm_strdup(info->arg);
                info->argv[1] = NULL;
            }
        }

        /* Count the number of arguments */
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i; /* Set the argument_count field*/

        /* Replace aliases in the arguments */
        replace_alias(info);

        /* Replace variables in the arguments */
        replace_vars(info);
    }
}

