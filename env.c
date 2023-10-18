#include "main.h"

/**
 * _myenv - Prints the environment variables.
 * @info: Pointer to the info_t struct containing command and argument information.
 *
 * This function prints the environment variables stored in the info_t struct.
 *
 * Returns:
 *   0 to indicate successful execution.
 */
int _myenv(shell_info *info)
{
	print_lnlist_string(info->env);
	return 0; /* Return 0 to indicate successful execution */
}


/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: Pointer to the info_t struct containing environment variables.
 * @name: The name of the environment variable to retrieve.
 *
 * Returns:
 *   - A pointer to the value of the environment variable if found.
 *   - NULL if the environment variable is not found.
 */
char *_getenv(shell_info *info, const char *name)
{
	linkedList_node *current_node = info->env;
	char *variable_value;

	while (current_node)
	{
		variable_value = starts_with(current_node->string, name);
		if (variable_value && *variable_value)
			return variable_value; /* Return the value of the environment variable */
		current_node = current_node->next;
	}
	return (NULL); /* Return NULL if the environment variable is not found */
}



/**
 * _mysetenv - Sets a new environment variable or updates an existing one.
 * @info: Pointer to the info_t struct containing environment variables.
 *
 *
 * Returns:
 *   - 0 on success.
 *   - 1 if incorrect number of arguments provided.
 */
int _mysetenv(shell_info *info)
{
	/* Check if the correct number of arguments is provided */
	if (info->argc != 3)
	{
		cm_eputs("Incorrect number of arguments\n");
		return 1; /* Return 1 for incorrect number of arguments */
	}

	/* Attempt to set the environment variable, return success/failure status */
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0); /* Return 0 on successful setenv operation */
	else
		return (1); /* Return 1 if setenv operation fails */
}



/**
 * _myunsetenv - Unsets specified environment variables.
 * @info: Pointer to the info_t struct containing arguments.
 *
 * This function unsets the environment variables specified in 'info->argv'.
 * If there are too few arguments, it prints an error message and returns 1.
 *
 * Return:
 * - 0 on success.
 * - 1 if there are too few arguments.
 */
int _myunsetenv(shell_info *info)
{
	int argIndex;

	/* Check if there are too few arguments */
	if (info->argc == 1)
	{
		cm_eputs("Too few arguments.\n");
		return (1); /* Return 1 indicating error */
	}

	/* Unset each environment variable specified in arguments */
	for (argIndex = 1; argIndex <= info->argc; argIndex++)
		_unsetenv(info, info->argv[argIndex]);

	return (0); /* Return 0 indicating success */
}


/**
 * populate_env_list - Populates the info_t structure's environment list.
 * @info: Pointer to the info_t struct.
 *
 *
 * Return:
 * - 0 on success.
 */
int populate_env_list(shell_info *info)
{
	linkedList_node *envList = NULL;  /* Temporary list for environment variables */
	size_t envIndex;

	/* Loop through environ array and add variables to the list */
	for (envIndex = 0; environ[envIndex]; envIndex++)
		add_node_end(&envList, environ[envIndex], 0);

	info->env = envList;  /* Assign the populated list to info->env */
	return 0;  /* Return 0 indicating success */
}


