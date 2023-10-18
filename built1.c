#include "main.h"


/**
 * set_alias - Sets or updates an alias in the alias list.
 * @info: Pointer to the information struct containing alias list.
 * @alias_definition: String containing alias name and its definition.
 *
 * Returns:
 *   0 on successful set or update of the alias.
 *   1 if the alias definition is empty or invalid.
 *   2 if memory allocation for the new alias node fails.
 */
int set_alias(shell_info *info, char *alias_definition)
{
    char *equals_sign_ptr;
    int set_result;

    equals_sign_ptr = cm_strchr(alias_definition, '=');

    /* If there is no '=' sign or the definition is empty, it's an invalid alias format */
    if (!equals_sign_ptr || !*(equals_sign_ptr + 1)) {
        return 1; /* Return 1 to indicate failure (invalid or empty alias definition) */
    }

    /* Unset the alias if it already exists */
    unset_alias(info, alias_definition);

    /* Add the new alias node to the alias list */
    set_result = add_node_end(&(info->aliases), alias_definition, 0) == NULL ? 2 : 0;

    return (set_result); /* Return set result: 0 for success, 1 for empty/invalid definition, 2 for memory allocation failure */
}

/**
 * print_alias - Prints the name and definition of an alias node.
 * @node: Pointer to the alias node to be printed.
 *
 * Returns:
 *   0 on successful printing of the alias.
 *   1 if the alias node is NULL (invalid).
 */
int print_alias(linkedList_node *node)
{
	char *equals_sign_ptr = NULL, *alias_name_ptr = NULL;

	if (node)
	{
		equals_sign_ptr = cm_strchr(node->string, '=');
		
		if (equals_sign_ptr)
		{
			/* Point to the beginning of the alias name */
			alias_name_ptr = node->string;

			/* Print alias name enclosed in single quotes */
			cm_putchar('\'');
			while (alias_name_ptr <= equals_sign_ptr)
            {
                /* Print each character of the alias name */
                cm_putchar(*alias_name_ptr++); 
            }
			/* Print alias definition */
			cm_puts("'");
            /* Print the alias definition */
			cm_puts(equals_sign_ptr + 1); 
			cm_puts("'\n");
            /* Return 0 to indicate successful printing */
			return (0); 
		}
	}
    /* Return 1 to indicate failure (invalid alias node) */
	return (1); 
}


/**
 * _myalias - Handles alias-related commands and operations.
 * @info: Pointer to the info_t struct containing command and argument information.
 *
 * Returns:
 *   0 on successful execution of the alias-related commands.
 */
int _myalias(shell_info *info)
{
	int arg_index = 1;
	char *equals_sign_ptr = NULL;
	linkedList_node *node = NULL;

	if (info->argc == 1)
	{
		/* Print all aliases */
		node = info->aliases;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0; /* Return 0 to indicate successful execution */
	}

	/* Handle alias setting/updating and printing */
	while (info->argv[arg_index])
	{
		equals_sign_ptr = cm_strchr(info->argv[arg_index], '=');

		if (equals_sign_ptr)
		{
			/* Set or update alias */
			set_alias(info, info->argv[arg_index]);
		}
		else
		{
			/* Print alias definition */
			print_alias(ln_startsWith(info->aliases, info->argv[arg_index], '='));
		}

		arg_index++;
	}

	return (0); /* Return 0 to indicate successful execution */
}
