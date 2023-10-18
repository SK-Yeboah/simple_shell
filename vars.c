#include "main.h"

/**
 * check_chain - Checks and modifies the buffer based on command chain type.
 * @info: Pointer to the info_t struct.
 * @buffer: Input buffer containing the command.
 * @position: Pointer to the current position in the buffer.
 * @command_start: Start position of the current command.
 * @buffer_length: Length of the input buffer.
 */
void check_chain(shell_info *info, char *buffer, size_t *position, size_t command_start, size_t buffer_length)
{
    size_t current_position = *position;

    /* Check if command chain type is CMD_AND */
    if (info->command_BufferType == COMMAND_AND)
    {
        /* If previous command had a non-zero exit status, terminate current command */
        if (info->status)
        {
            buffer[command_start] = 0; /* Replace the command chain symbol with a null character */
            current_position = buffer_length; /* Set the position to the end of the buffer */
        }
    }
    /* Check if command chain type is CMD_OR */
    else if (info->command_BufferType == COMMAND_OR)
    {
        /* If previous command had a zero exit status, terminate current command */
        if (!info->status)
        {
            buffer[command_start] = 0; /* Replace the command chain symbol with a null character */
            current_position = buffer_length; /* Set the position to the end of the buffer */
        }
    }

    *position = current_position; /* Update the position pointer */
}






/**
 * is_chain - Checks if the current position in the buffer represents a command chain.
 * @info: Pointer to the info_t struct.
 * @buffer: Input buffer containing the command.
 * @position: Pointer to the current position in the buffer.
 *
 * Return: 1 if a command chain is found, 0 otherwise.
 */
int is_chain(shell_info *info, char *buffer, size_t *position)
{
    size_t current_position = *position;

    /* Check for logical OR operator '||' */
    if (buffer[current_position] == '|' && buffer[current_position + 1] == '|')
    {
        buffer[current_position] = 0; /* Replace '|' with null character to separate commands */
        current_position++;
        info->command_BufferType = COMMAND_OR; /* Set command buffer type to CMD_OR */
    }
    /* Check for logical AND operator '&&' */
    else if (buffer[current_position] == '&' && buffer[current_position + 1] == '&')
    {
        buffer[current_position] = 0; /* Replace '&' with null character to separate commands */
        current_position++;
        info->command_BufferType = COMMAND_AND; /* Set command buffer type to CMD_AND */
    }
    /* Check for command termination ';' */
    else if (buffer[current_position] == ';')
    {
        buffer[current_position] = 0; /* Replace semicolon with null character to mark the end of this command */
        info->command_BufferType = COMMAND_CHAIN; /* Set command buffer type to CMD_CHAIN */
    }
    else
    {
        return 0; /* No command chain found, return 0 */
    }

    *position = current_position; /* Update the position pointer */
    return 1; /* Command chain found, return 1 */
}


/**
 * replace_alias - Replaces alias in the argv[0] of info_t struct.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int replace_alias(shell_info *info)
{
    int attempts_left;
    linkedList_node *alias_node;
    char *alias_value, *equal_sign_position;

    for (attempts_left = 10; attempts_left > 0; attempts_left--)
    {
        alias_node = ln_startsWith(info->aliases, info->argv[0], '=');

        /* If no alias found, return 0 */
        if (!alias_node)
            return 0;

        free(info->argv[0]);

        /* Find the position of '=' character in the alias string */
        equal_sign_position = cm_strchr(alias_node->string, '=');

        /* If '=' not found, return 0 */
        if (!equal_sign_position)
            return 0;

        /* Extract the alias value and duplicate it */
        alias_value = cm_strdup(equal_sign_position + 1);

        /* If strdup fails, return 0 */
        if (!alias_value)
            return 0;

        info->argv[0] = alias_value; /* Set argv[0] to the alias value */
    }

    return (1); /* Successful alias replacement */
}



/**
 * replace_string - Replaces an old dynamically allocated string with a new one.
 * @old_str_ptr: Pointer to the pointer holding the old string.
 * @new_str: New string to replace the old one.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int replace_string(char **old_str_ptr, char *new_str)
{
    /* Free the memory occupied by the old string */
    free(*old_str_ptr);
    
    /* Set the pointer to the new string */
    *old_str_ptr = new_str;
    
    return (*old_str_ptr != NULL); /* Return 1 if the replacement is successful, 0 otherwise */
}



/**
 * replace_vars - Replaces environment variables in the argv of info_t struct.
 * @info: Pointer to the info_t struct.
 *
 * Return: 0 (always).
 */
int replace_vars(shell_info *info)
{
    int arg_index;
    linkedList_node *env_node;

    for (arg_index = 0; info->argv[arg_index]; arg_index++)
    {
        char *current_arg = info->argv[arg_index];

        /* Skip non-environment variables */
        if (current_arg[0] != '$' || !current_arg[1])
            continue;

        /* Replace $? with the exit status */
        if (!cm_strcmp(current_arg, "$?"))
        {
            replace_string(&(info->argv[arg_index]), cm_strdup(convert_number(info->status, 10, 0)));
            continue;
        }

        /* Replace $$ with the process ID */
        if (!cm_strcmp(current_arg, "$$"))
        {
            replace_string(&(info->argv[arg_index]), cm_strdup(convert_number(getpid(), 10, 0)));
            continue;
        }

        /* Replace environment variables */
        env_node = ln_startsWith(info->env, &current_arg[1], '=');
        if (env_node)
        {
            char *env_value = cm_strchr(env_node->string, '=') + 1;
            replace_string(&(info->argv[arg_index]), cm_strdup(env_value));
            continue;
        }

        /* If no match is found, replace with an empty string */
        replace_string(&info->argv[arg_index], cm_strdup(""));
    }

    return (0);
}

