#include "main.h"


/**
 * _setenv - Sets an environment variable with a given value.
 * @info: The information struct containing environment data.
 * @var: The variable name.
 * @value: The value to be set.
 *
 * Return: 0 on success, 1 on failure.
 */
int _setenv(shell_info *info, char *var, char *value)
{
	char *new_env_entry = NULL;
	linkedList_node *node;
	char *p;

	if (!var || !value)
		return 1;

	new_env_entry = malloc(cm_strlen(var) + cm_strlen(value) + 2);
	if (!new_env_entry)
		return 1;

	cm_strcpy(new_env_entry, var);
	cm_strcat(new_env_entry, "=");
	cm_strcat(new_env_entry, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = new_env_entry;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), new_env_entry, 0);
	free(new_env_entry);
	info->env_changed = 1;
	return (0);
}


/**
 * _unsetenv - Unsets an environment variable.
 * @info: The information struct containing environment data.
 * @env_var: The variable name to be unset.
 *
 * Return: 0 on success, 1 on failure.
 */
int _unsetenv(shell_info *info, char *env_var)
{
	linkedList_node *current_node = info->env;
	size_t index = 0;
	char *equal_sign;

	if (!current_node || !env_var)
		return (0);

	while (current_node)
	{
		equal_sign = starts_with(current_node->string, env_var);
		if (equal_sign && *equal_sign == '=')
		{
			info->env_changed = delete_nodeint_at_index(&(info->env), index);
			index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}
	return (info->env_changed);
}


/**
 * get_environ - Retrieves environment variables from the info struct.
 * @info: The information struct containing environment data.
 *
 * Return: Pointer to the array of environment variables.
 */
char **get_environ(shell_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


